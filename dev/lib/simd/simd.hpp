/*
 * File: simd/simd.hpp
 * Purpose: SIMD C++ library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the BSL 1.0 license.
 */

#pragma once

#include <lib/core/includes.hpp>

/// @author Amlal El Mahrouss
/// @brief Basic SIMD processor.

namespace ocl::snu::simd
{
	template <typename backend_type>
	class basic_simd_processor
	{
	private:
		backend_type backend_;

		enum opcode
		{
			bad = 0,
			add,
			mul,
			div,
			invalid = 0xfff,
		};

	public:
		basic_simd_processor()			= default;
		virtual ~basic_simd_processor() = default;

		basic_simd_processor& operator=(const basic_simd_processor&) = delete;
		basic_simd_processor(const basic_simd_processor&)			 = delete;

		typename backend_type::register_type& call(const opcode& op, typename backend_type::register_type& lhs, typename backend_type::register_type& rhs)
		{
			switch (op)
			{
			case add:
				return backend_.add(lhs, rhs);
			case mul:
				return backend_.mul(lhs, rhs);
			case div:
				return backend_.div(lhs, rhs);
			default:
				break;
			}

			return backend_.is_bad();
		}

		std::basic_string<char> isa()
		{
			return backend_.isa();
		}
	};
} // namespace ocl::snu::simd
