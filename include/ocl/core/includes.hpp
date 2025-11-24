/*
 * File: core/config.hpp
 * Purpose: Config file of the OCL.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#pragma once

#include <memory>
#include <iostream>
#include <string>

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