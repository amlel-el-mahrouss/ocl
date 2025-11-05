/*
 * File: tests/hpptest.hpp
 * Purpose: HPP Test wrapper for the OCL library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss 
 */

#pragma once

namespace scl::hpptest
{
	typedef bool condition_type;

	template <condition_type expr = true>
	consteval inline void must_pass()
	{
#ifdef SCL_HPPTEST
		SCL_HPPTEST_ASSERT(expr);
#endif
	}
} // namespace scl::hpptest
