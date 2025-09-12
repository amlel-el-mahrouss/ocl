/*
 * File: simd/basic_simd.hpp
 * Purpose: Basic SIMD backend C++ library.
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss, and SNU Systems, Corp, licensed under the BSL 1.0 license.
 */

#pragma once

#include <lib/core/includes.hpp>
#include <cmath>

#ifdef __x86_64__
#include <immintrin.h>

using simd_type = __m256;
#endif

#ifdef __aarch64__
#include <arm_neon.h>

using simd_type = float32x4_t;
#endif

namespace ocl::snu::simd
{
	struct basic_simd_backend final
	{
		struct simd_traits final
		{
			simd_type __val;

		private:
			static bool bad;
			friend class basic_simd_backend;
		};

		using register_type = simd_traits;

		const bool& is_bad() noexcept
		{
			return register_type::bad;
		}

		std::basic_string<char> isa()
		{
			return "basic-backend";
		}
	};
} // namespace ocl::snu::simd
