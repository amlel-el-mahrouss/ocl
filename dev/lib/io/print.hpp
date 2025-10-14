/*
 * File: print.hpp
 * Purpose: OCL Print library
 * Author: Amlal El Mahrouss. (amlal@nekernel.org)
 * Copyright 2025
 */

#ifndef _SCL_PRINT_HPP
#define _SCL_PRINT_HPP

#include <iostream>
#include <ostream>

namespace scl::io
{
	template <typename T, typename... Args>
	inline void print(T fmt, Args... other) noexcept
	{
		std::cout << fmt;
		print(other...);
	}

	template <typename T>
	inline void print(T fmt) noexcept
	{
		std::cout << fmt;
	}

	inline void print() noexcept
	{
		std::cout << std::endl;
	}

	template <typename... T>
	inline void println(T... fmt) noexcept
	{
		print(fmt...);
		print();
	}
} // namespace scl::io

#endif // ifndef _SCL_PRINT_HPP
