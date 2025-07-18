/*
 * File: memory/tracked_ptr.hpp
 * Purpose: Custom smart pointer implementation in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp all rights reserved.
 */

#pragma once

#include <cstddef>
#include <utility>
#include <memory>

namespace snu::memory
{
	template <typename T>
	class tracked_allocator;

	template <typename T>
	class tracked_mgr;

	template <typename T, typename Mgr>
	class tracked_ptr;

	template <typename T>
	class tracked_allocator
	{
	public:
		std::size_t allocated_count_   = 0;
		std::size_t deallocated_count_ = 0;
		bool		is_initialized_	   = false;

	public:
		template <typename... U>
		void allocate(T*& ptr, U&&... args)
		{
			if (!is_initialized_)
			{
				is_initialized_ = true;
			}

			ptr = new T(args...);

			if (ptr)
			{
				++allocated_count_;
			}
			else
			{
				throw std::bad_alloc();
			}
		}

		void deallocate(T*& ptr)
		{
			if (ptr)
			{
				if (allocated_count_)
					--allocated_count_;

				++deallocated_count_;

				::operator delete(ptr);
				ptr = nullptr;
			}
		}
	};

	template <typename T>
	class tracked_mgr
	{
	private:
		tracked_allocator<T> allocator_;

	public:
		const tracked_allocator<T>& allocator()
		{
			return allocator_;
		}

		template <typename... U>
		T* retain(U&&... args)
		{
			T* ptr = nullptr;
			allocator_.allocate(ptr, std::forward<U>(args)...);
			return ptr;
		}

		void dispose(T* ptr)
		{
			allocator_.deallocate(ptr);
		}
	};

	template <typename T, typename Mgr = tracked_mgr<T>>
	class tracked_ptr
	{
	public:
		static Mgr& manager()
		{
			static Mgr mgr;
			return mgr;
		}

	public:
		template <typename... U>
		explicit tracked_ptr(U&&... args)
			: ptr_(nullptr)
		{
			ptr_ = tracked_ptr::manager().retain(std::forward<U>(args)...);
		}

		~tracked_ptr() noexcept
		{
			tracked_ptr::manager().dispose(ptr_);
		}

		tracked_ptr(const tracked_ptr&)			   = delete;
		tracked_ptr& operator=(const tracked_ptr&) = delete;

	public:
		T* get() const
		{
			return ptr_;
		}

		T* data()
		{
			return ptr_;
		}

		T& operator*() const
		{
			return *ptr_;
		}

		T* operator->() const
		{
			return ptr_;
		}

		explicit operator bool() const
		{
			return ptr_ != nullptr;
		}

		void swap(tracked_ptr& other)
		{
			std::swap(ptr_, other.ptr_);
		}

	public:
		tracked_ptr(tracked_ptr&& other) noexcept
			: ptr_(other.ptr_)
		{
			other.ptr_ = nullptr;
		}

		tracked_ptr& operator=(tracked_ptr&& other) noexcept
		{
			if (this != &other)
			{
				this->reset();
				ptr_	   = other.ptr_;
				other.ptr_ = nullptr;
			}

			return *this;
		}

	private:
		T* ptr_ = nullptr;
	};

	template <typename T>
	inline auto make_tracked(T arg) -> auto {
		return tracked_ptr<T>{std::forward<T>(arg)};
	}


	template <typename U, typename... T>
	inline auto make_tracked(T&&... arg) -> auto {
		return tracked_ptr<U>{std::forward<T>(arg)...};
	}
} // namespace snu::memory