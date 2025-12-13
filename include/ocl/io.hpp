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
#define console_io_out ::ocl::io::null_cout
#define console_io_in  ::ocl::io::null_cin

#warning The OCL doesn't define IO streams in a freestanding host.

namespace ocl::io
{
	class nullable_stream final
	{
		nullable_stream()		   = default;
		~nullable_stream() = default;

        nullable_stream& operator<<(...) = delete;
        nullable_stream& operator>>(...) = delete;
	}

	inline nullable_stream null_cout;
	inline nullable_stream null_cin;
} // namespace ocl::io

#endif
#endif