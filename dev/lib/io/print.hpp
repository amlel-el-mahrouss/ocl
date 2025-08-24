/*
 * File: print.hpp
 * Purpose: SNU Print library
 * Author: Amlal El Mahrouss. (founder@snu.systems)
 * Copyright 2025, SNU Systems Corp.
 */

#ifndef _SNU_PRINT_HPP
#define _SNU_PRINT_HPP

#include <iostream>
#include <ostream>

namespace snu::io
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
	}
} // namespace snu::io

#endif // ifndef _SNU_PRINT_HPP
