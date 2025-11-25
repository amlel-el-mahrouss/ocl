/*
 * File: memory/tracked_ptr.hpp
 * Purpose: Strict pointer type implementation in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#pragma once

#include <cstddef>
#include <utility>
#include <new>
#include <atomic>

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

namespace ocl::memory
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
		std::atomic<size_t> allocated_count_   = 0;
		std::atomic<size_t> deallocated_count_ = 0;

	public:
		explicit tracked_allocator() = default;
		virtual ~tracked_allocator() = default;

		tracked_allocator& operator=(const tracked_allocator&) = default;
		tracked_allocator(const tracked_allocator&)			   = default;

	public:
		using pointer_type = T*;

		template <typename... U>
		void retain(pointer_type& ptr, U&&... args)
		{
			ptr = new T(std::forward<U>(args)...);

			if (ptr)
			{
				++allocated_count_;
				return;
			}

			throw std::bad_alloc();
		}

		template <typename... U>
		void must_retain(pointer_type& ptr, U&&... args) noexcept
		{
			this->retain(ptr, args...);
		}

		void dispose(pointer_type& ptr) noexcept
		{
			if (ptr)
			{
				if (allocated_count_)
					--allocated_count_;

				++deallocated_count_;

				delete ptr;
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
		explicit tracked_mgr() = default;
		virtual ~tracked_mgr() = default;

		tracked_mgr& operator=(const tracked_mgr&) = default;
		tracked_mgr(const tracked_mgr&)			   = default;

	public:
		using pointer_type = T*;

		const tracked_allocator<T>& allocator() noexcept
		{
			return allocator_;
		}

		template <typename... U>
		pointer_type retain(U&&... args)
		{
			pointer_type ptr = nullptr;
			allocator_.retain(ptr, std::forward<U>(args)...);

			return ptr;
		}

		template <typename... U>
		pointer_type must_retain(U&&... args) noexcept
		{
			return this->retain(std::forward<U>(args)...);
		}

		void dispose(pointer_type& ptr) noexcept
		{
			allocator_.dispose(ptr);
		}
	};

	template <typename T, typename Mgr = tracked_mgr<T>>
	class tracked_ptr
	{
	public:
		static Mgr& manager() noexcept
		{
			static Mgr mgr;
			return mgr;
		}

	public:
		template <typename... U>
		tracked_ptr(U&&... args)
			: ptr_(nullptr)
		{
			ptr_ = tracked_ptr::manager().retain(std::forward<U>(args)...);
		}

		virtual ~tracked_ptr() noexcept
		{
			this->reset();
		}

		tracked_ptr(const tracked_ptr&)			   = delete;
		tracked_ptr& operator=(const tracked_ptr&) = delete;

	public:
		using pointer_type = T*;

		void reset()
		{
			if (ptr_)
			{
				tracked_ptr::manager().dispose(ptr_);
			}
		}

		pointer_type get() const
		{
			return ptr_;
		}

		pointer_type data()
		{
			return ptr_;
		}

		T& operator*() const
		{
			return *ptr_;
		}

		pointer_type operator->() const
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
		pointer_type ptr_{nullptr};
	};

	template <typename T>
	inline auto make_tracked() -> tracked_ptr<T>
	{
		return tracked_ptr<T>();
	}

	template <typename U, typename... T>
	inline auto make_tracked(T&&... arg) -> tracked_ptr<U>
	{
		return tracked_ptr<U>(std::forward<T>(arg)...);
	}

	template <typename T>
	inline void swap(tracked_ptr<T>& a, tracked_ptr<T>& b)
	{
		a.swap(b);
	}

	/// @brief a Must Pass function is a standard way to verify a container' validity, inspired from NeKernel/VMKernel.
	template <typename T, typename error_handler>
	inline void must_pass(tracked_ptr<T>& ptr, error_handler handler)
	{
		if (ptr.manager().allocator().allocated_count_ < ptr.manager().allocator().deallocated_count_)
		{
			handler.template error<true>("Invalid TrackedPtr detected: Deallocated count exceeds allocated count.");
		}
	}
} // namespace ocl::memory
