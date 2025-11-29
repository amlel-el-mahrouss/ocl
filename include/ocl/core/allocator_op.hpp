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
	class allocator_op
	{
		allocator_new	 m_alloc_{};
		allocator_delete m_free_{};

	public:
		allocator_op()	= default;
		~allocator_op() = default;

		allocator_op& operator=(const allocator_op&) = delete;
		allocator_op(const allocator_op&)			 = delete;

		ret_type* claim()
		{
			return m_alloc_();
		}

		template <typename... var_type>
		auto construct(var_type... args) -> std::shared_ptr<ret_type>
		{
			return std::shared_ptr<ret_type>(m_alloc_.template var_alloc<var_type...>(args...), allocator_delete{});
		}

		void unclaim(ret_type* ptr)
		{
			m_free_(ptr);
		}
	};

	template <typename type>
	using allocator_type = allocator_op<type, new_op<type>, delete_op<type>>;
} // namespace ocl

#endif // ifndef _OCL_ALLOCATOR_SYSTEM_HPP