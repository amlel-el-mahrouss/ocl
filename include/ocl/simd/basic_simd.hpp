/*
 * File: simd/basic_simd.hpp
 * Purpose: Basic SIMD backend C++ library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the BSL 1.0 license.
 */

#pragma once

#include <core/config.hpp>

#ifdef __x86_64__
#include <immintrin.h>
#endif

#ifdef __aarch64__
#include <arm_neon.h>
#endif

namespace ocl::simd
{
	struct OCL_DEPRECATED_MSG("Unmaintained since v1.0.51") basic_simd final
	{
#ifdef __x86_64__
		using simd_type = __m256;
#endif

#ifdef __aarch64__
		using simd_type = float32x4_t;
#endif

		struct simd_traits final
		{
			simd_type __val;

		private:
			static bool bad;
			friend class basic_simd;
		};

		using register_type = simd_traits;

		const bool& is_bad() noexcept
		{
			return register_type::bad;
		}

		std::basic_string<char> isa()
		{
			return "basic_simd";
		}
	};
} // namespace ocl::simd
