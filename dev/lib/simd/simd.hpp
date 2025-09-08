/*
 * File: simd/simd.hpp
 * Purpose: SIMD C++ library.
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss, and SNU Systems, Corp, licensed under the BSL 1.0 license.
 */

#pragma once

#include <lib/core/includes.hpp>

/// @author Amlal El Mahrouss
/// @brief Basic SIMD processor.

namespace ocl::snu::simd
{
	template <typename SimdBackend>
	class basic_simd_processor
	{
	private:
		SimdBackend processor_;

		enum opcode
		{
			bad,
			add,
			mul,
			div,
		};

	public:
		basic_simd_processor()			= default;
		virtual ~basic_simd_processor() = default;

		basic_simd_processor& operator=(const basic_simd_processor&) = delete;
		basic_simd_processor(const basic_simd_processor&)			 = delete;

		typename SimdBackend::Register& call(const opcode& op, typename SimdBackend::Register& lhs, typename SimdBackend::Register& rhs)
		{
			switch (op)
			{
			case add:
				return processor_.add(lhs, rhs);
			case mul:
				return processor_.mul(lhs, rhs);
			case div:
				return processor_.div(lhs, rhs);
			default:
				break;
			}
			return SimdBackend::Register::bad;
		}

		std::basic_string<char> isa()
		{
			return processor_.isa();
		}
	};
} // namespace ocl::snu::simd
