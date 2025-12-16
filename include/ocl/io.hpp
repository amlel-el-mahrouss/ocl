/*
 * File: print.hpp
 * Purpose: OCL Print library
 * Author: Amlal El Mahrouss. (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, Licensed under the Boost Software License. Licensed under the BSL 1.0 license
 */

#ifndef __OCL_CORE_IO
#define __OCL_CORE_IO

#include <ocl/detail/config.hpp>

#ifndef __OCL_FREESTANDING
#define console_io_out std::cout
#define console_io_in  std::cin

#include <iostream>
#else
#define console_io_out ::ocl::io::void_cout
#define console_io_in  ::ocl::io::void_cin

#warning The OCL doesn't define IO streams in a freestanding host.

namespace ocl::io
{
	class void_stream final
	{
		void_stream()  = default;
		~void_stream() = default;

		void_stream& operator<<(...) = delete;
		void_stream& operator>>(...) = delete;
	}

	inline void_stream void_cout;
	inline void_stream void_cin;
} // namespace ocl::io

#endif
#endif