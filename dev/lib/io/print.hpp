/*
 * File: print.hpp
 * Purpose: OCL Print library
 * Author: Amlal El Mahrouss. (amlal@nekernel.org)
 * Copyright 2025
 */

#ifndef _OCL_PRINT_HPP
#define _OCL_PRINT_HPP

#include <iostream>

namespace ocl::io
{
	template <typename T>
	inline void print(T fmt) noexcept
	{
		std::cout << fmt;
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
		std::cout << fmt;
		print(other...);
	}

	template <typename... T>
	inline void println(T... fmt) noexcept
	{
		print(fmt...);
		print("\n");
	}
} // namespace ocl::io

#endif // ifndef _OCL_PRINT_HPP
