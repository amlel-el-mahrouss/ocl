/*
 * File: opt.hpp
 * Author: Amlal El Mahrouss,
 * Copyright 2023-2025, Amlal El Mahrouss
 */

#ifndef _SCL_ERR_HPP
#define _SCL_ERR_HPP

#include <stdexcept>

namespace scl
{
	using runtime_error = std::runtime_error;
	using fix_error		= runtime_error;
	using math_error	= runtime_error;
	using cgi_error		= runtime_error;
} // namespace scl

#endif // _SCL_ERR_HPP