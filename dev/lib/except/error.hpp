/*
 * File: opt.hpp
 * Author: Amlal El Mahrouss,
 * Copyright 2023-2025, Amlal El Mahrouss/SNU Systems Corp.
 */

#ifndef _SNU_ERR_HPP
#define _SNU_ERR_HPP

#include <stdexcept>

namespace snu::except
{
	using runtime_error = std::runtime_error;
	using fix_error		= runtime_error;
	using math_error	= runtime_error;
	using cgi_error		= runtime_error;
} // namespace snu::except

#endif // _SNU_ERR_HPP