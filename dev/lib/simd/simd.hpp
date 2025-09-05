/*
 * File: simd/simd.hpp
 * Purpose: SIMD C++ library.
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss, and SNU Systems, Corp, licensed under the BSL 1.0 license.
 */

#pragma once

#include <lib/core/includes.hpp>

namespace ocl::snu::simd
{
  struct simd_backend;

  template <typename SimdBackend>
  struct basic_simd;
}
