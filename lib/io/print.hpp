/*
 * File: print.hpp
 * Purpose: SNU Print library
 * Author: Amlal El Mahrouss. (founder@snu.systems)
 * Copyright 2025, SNU Systems Corp all rights reserved.
 */

#ifndef _STDX_PRINT_HPP
#define _STDX_PRINT_HPP

#include <iostream>

namespace snu
{
	template <typename... T>
	inline void print(const T&... fmt)
	{
		std::cout << std::forward(fmt...);
	}

	template <typename... T>
	inline void println(T... fmt)
	{
		std::cout << std::move(fmt...);
		std::cout << std::endl;
	}
} // namespace snu

#endif // ifndef _STDX_PRINT_HPP