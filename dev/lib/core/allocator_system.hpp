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
	struct new_op final
	{
		template <typename type>
		inline auto operator()() -> type*
		{
			return new type;
		}

		template <typename type, typename... var_type>
		inline auto operator()(var_type&&... args) -> type*
		{
			return new type{std::forward(args...)};
		}
	};

	struct delete_op final
	{
		template <typename type>
		inline auto operator()(type* t) -> void
		{
			delete t;
		}
	};

	template <typename allocator_new, typename allocator_delete>
	class allocator_system
	{
		allocator_delete del_;

	public:
		allocator_system()	= default;
		~allocator_system() = default;

		allocator_system& operator=(const allocator_system&) = delete;
		allocator_system(const allocator_system&)			 = delete;

		template <typename ret_type>
		ret_type* claim() noexcept
		{
			return allocator_new(sizeof(ret_type));
		}

		template <typename ret_type, typename... var_type>
		auto construct(var_type&&... args) -> std::shared_ptr<ret_type>
		{
			return std::shared_ptr<ret_type>(allocator_new(ret_type{std::forward(args...)}), del_());
		}

		template <typename ret_type>
		void unclaim(ret_type* ptr)
		{
			del_(ptr);
		}
	};

	using standard_allocator_type = allocator_system<new_op, delete_op>;
} // namespace ocl

#endif // ifndef _OCL_ALLOCATOR_SYSTEM_HPP
