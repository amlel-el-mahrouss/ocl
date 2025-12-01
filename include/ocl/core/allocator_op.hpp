/*
 * File: core/allocator_op.hpp
 * Purpose: Allocator System container.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, Licensed under the Boost Software License. Licensed under the BSL 1.0 license
 */

#ifndef _OCL_ALLOCATOR_SYSTEM_HPP
#define _OCL_ALLOCATOR_SYSTEM_HPP

#include <core/config.hpp>
#include <memory>

namespace ocl
{
	/// @note these are guidelines on allocating a resource
	template <typename type>
	struct global_new_op final
	{
		inline auto operator()() -> type*
		{
			return new type;
		}

		template <typename... var_type>
		inline auto var_alloc(var_type&&... args) -> type*
		{
			return new type{std::forward<var_type>(args)...};
		}
	};

	/// @note these are guidelines on deleting a resource
	template <typename type>
	struct global_delete_op final
	{
		inline auto operator()(type* t) -> void
		{
			delete t;
		}
	};

	template <typename ret_type, typename allocator_new, typename allocator_delete>
	class allocator_op
	{
		allocator_new	 alloc_op_{};
		allocator_delete free_op_{};

	public:
		allocator_op()	= default;
		~allocator_op() = default;

		allocator_op& operator=(const allocator_op&) = delete;
		allocator_op(const allocator_op&)			 = delete;

		template <typename... var_type>
		auto construct(var_type&&... args) -> std::shared_ptr<ret_type>
		{
			return std::shared_ptr<ret_type>(alloc_op_.template var_alloc<var_type...>(args...), free_op_);
		}
	};

	template <typename type>
	using allocator = allocator_op<type, global_new_op<type>, global_delete_op<type>>;
} // namespace ocl

#endif // ifndef _OCL_ALLOCATOR_SYSTEM_HPP