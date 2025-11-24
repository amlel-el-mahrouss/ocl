/*
 * File: opt.hpp
 * Author: Amlal El Mahrouss,
 * Copyright 2023-2025, Amlal El Mahrouss, Licensed under the Boost Software License
 */

#ifndef _OCL_ERR_HPP
#define _OCL_ERR_HPP

#include <stdexcept>
#include <core/error_handler.hpp>

namespace ocl::error
{
	using runtime_error = std::runtime_error;
	using fix_error		= runtime_error;
	using math_error	= runtime_error;
	using cgi_error		= runtime_error;
} // namespace ocl::error

#endif // _OCL_ERR_HPP