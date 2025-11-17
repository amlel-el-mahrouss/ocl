/*
 * File: tests/hpptest.hpp
 * Purpose: HPP Test wrapper for the OCL library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the MIT license.
 */

#pragma once

namespace ocl::hpptest
{
	typedef bool condition_type;

	template <condition_type expr = true>
	consteval inline void must_pass()
	{
#ifdef OCL_HPPTEST
		OCL_HPPTEST_ASSERT(expr);
#endif
	}
} // namespace ocl::hpptest
