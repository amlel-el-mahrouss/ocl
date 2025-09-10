/*
 * File: simd/avx.hpp
 * Purpose: AVX C++ library.
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss, and SNU Systems, Corp, licensed under the BSL 1.0 license.
 */

#pragma once

#include <lib/core/includes.hpp>

namespace ocl::snu::simd
{
	struct avx_256_backend final
	{
		std::basic_string<char> isa()
		{
			return "AVX-256";
		}
	};
} // namespace ocl::snu::simd
