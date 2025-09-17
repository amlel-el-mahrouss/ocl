/*
 * File: core/allocator_system.hpp
 * Purpose: Allocator System container.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss. Licensed under the BSL 1.0 license
 */

#ifndef _OCL_ALLOCATOR_SYSTEM_HPP
#define _OCL_ALLOCATOR_SYSTEM_HPP

#include <lib/core/includes.hpp>
#include <stdexcept>
#include <memory>

namespace ocl
{
	template <typename type>
	struct new_op final
	{
		inline auto operator()() -> type*
		{
			return new type;
		}

		template <typename... var_type>
		inline auto var_alloc(var_type... args) -> type*
		{
			return new type{args...};
		}
	};

	template <typename type>
	struct delete_op final
	{
		inline auto operator()(type* t) -> void
		{
			delete t;
		}
	};

	template <typename ret_type, typename allocator_new, typename allocator_delete>
	class allocator_system
	{
		allocator_new	 alloc_;
		allocator_delete del_;

	public:
		allocator_system()	= default;
		~allocator_system() = default;

		allocator_system& operator=(const allocator_system&) = delete;
		allocator_system(const allocator_system&)			 = delete;

		ret_type* claim() noexcept
		{
			return alloc_();
		}

		template <typename... var_type>
		auto construct(var_type... args) -> std::shared_ptr<ret_type>
		{
			return std::shared_ptr<ret_type>(alloc_.template var_alloc<var_type...>(args...), allocator_delete{});
		}

		void unclaim(ret_type* ptr)
		{
			del_(ptr);
		}
	};

	template <typename type>
	using standard_allocator_type = allocator_system<type, new_op<type>, delete_op<type>>;
} // namespace ocl

#endif // ifndef _OCL_ALLOCATOR_SYSTEM_HPP
