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
#define console_io_in  std::cin

namespace ocl::io
{
	template <typename T>
	inline void print(T fmt) noexcept
	{
		console_io_out << fmt;
	}

	inline void print() noexcept
	{
	}

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

	namespace detail
	{
		inline bool is_stdio_sync = true;
	}

	inline void enable_stdio_sync(const bool& enable) noexcept
	{
		console_io_out.sync_with_stdio(enable);
		detail::is_stdio_sync = false;
	}

	inline const bool& is_stdio_sync()
	{
		return detail::is_stdio_sync;
	}

	inline void lf() noexcept
	{
#ifdef OCL_USE_CRLF_ENDINGS
		print("\r\n");
#else
		print("\n");
#endif
	}

	template <typename... T>
	inline void println(T... fmt) noexcept
	{
		print(fmt...);
		lf();
	}
} // namespace ocl::io

#endif // ifndef _OCL_PRINT_HPP
