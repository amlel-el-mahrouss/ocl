/*
 * File: print.hpp
 * Purpose: SNU Print library
 * Author: Amlal El Mahrouss. (founder@snu.systems)
 * Copyright 2025, SNU Systems Corp.
 */

#ifndef _SNU_PRINT_HPP
#define _SNU_PRINT_HPP

#include <initializer_list>
#include <iostream>
#include <ostream>

namespace snu::io
{	
	template <typename T>
	inline void printv(T fmt) noexcept
	{
		std::cout << fmt;
	}

	template <typename T>
	inline void printv(std::initializer_list<T> fmt) noexcept
	{
		std::cout << fmt;
	}

	template <typename... T>
	inline void print(T... fmt) noexcept
	{
		(printv(fmt), ...);
	}

	template <typename... T>
	inline void println(T... fmt) noexcept
	{
		print(static_cast<T>(fmt)...);
		std::cout << std::endl;
	}
} // namespace snu::io

#endif // ifndef _SNU_PRINT_HPP