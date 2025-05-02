/*
 * File: fix.hpp
 * Purpose: Financial Information Protocol implementation in C++.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss all rights reserved.
 */

#ifndef _STDX_FIX_HPP
#define _STDX_FIX_HPP

#include <cstdint>
#include <cstddef>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>

namespace astdx::fix
{
	struct fix_reader;
	struct fix_writer;
	struct fix_visitor;
	struct fix_range;

	/// @brief Buffer+Length structure
	typedef fix_range* fix_range_ptr_t;

	struct fix_range final
	{
		char*	 ascii_bytes_;
		uint16_t length_;
	};
} // namespace astdx::fix

#endif // ifndef _STDX_FIX_HPP
