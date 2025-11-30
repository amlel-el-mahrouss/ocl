/*
 * File: print.hpp
 * Purpose: OCL Print library
 * Author: Amlal El Mahrouss. (amlal@nekernel.org)
 * Copyright 2025
 */

#ifndef _OCL_PRINT_HPP
#define _OCL_PRINT_HPP

#include <core/config.hpp>

#include <iostream>

#define console_io_out std::cout

namespace ocl::io
{
	template <typename T>
	inline void print(T fmt) noexcept
	{
		console_io_out << fmt;
	}

	inline void print() noexcept {}

	template <typename... Args>
	inline void print(Args... fmt) noexcept
	{
		print(fmt...);
		print();
	}

	template <typename T, typename... Args>
	inline void print(T fmt, Args... other) noexcept
	{
		console_io_out << fmt;
		print(other...);
	}

	template <typename... T>
	inline void println(T... fmt) noexcept
	{
		print(fmt...);

#ifdef _WIN32
		print("\r\n");
#else
		print("\n");
#endif
	}
} // namespace ocl::io

#undef console_io_out

#endif // ifndef _OCL_PRINT_HPP
