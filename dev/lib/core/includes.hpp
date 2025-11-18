/*
 * File: core/includes.hpp
 * Purpose: Core includes for the OCL library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the MIT license.
 */

#pragma once

#include <boost/config.hpp>
#include <boost/core/nvp.hpp>
#include <boost/core/demangle.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/container/allocator.hpp>

namespace ocl
{
#ifdef OCL_USE_UTF8
	using char_type = char8_t;
#else
	using char_type = char;
#endif
} // namespace ocl