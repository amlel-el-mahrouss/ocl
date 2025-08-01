/*
 * File: print.hpp
 * Purpose: SNU Print library
 * Author: Amlal El Mahrouss. (founder@snu.systems)
 * Copyright 2025, SNU Systems Corp all rights reserved.
 */

#ifndef _SNU_PRINT_HPP
#define _SNU_PRINT_HPP

#include <iostream>

namespace snu::io
{
	template <typename... T>
	inline void print(T... fmt)
	{
		std::cout << std::move(fmt...);
	}

	template <typename... T>
	inline void println(T... fmt)
	{
		std::cout << std::move(fmt...);
		std::cout << std::endl;
	}
} // namespace snu::io

#endif // ifndef _SNU_PRINT_HPP