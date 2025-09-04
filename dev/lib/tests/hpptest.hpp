/*
 * File: tests/hpptest.hpp
 * Purpose: HPP Test wrapper for the OCL library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss 
 */

#pragma once

#ifdef OCL_HPPTEST
namespace ocl::hpptest
{
	typedef bool condition_type;

	template <condition_type expr = true>
	consteval inline void must_pass()
	{
		OCL_HPPTEST_ASSERT(expr);
	}
} // namespace ocl::hpptest
#endif
