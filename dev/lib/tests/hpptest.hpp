/*
 * File: tests/hpptest.hpp
 * Purpose: HPP Test wrapper for the SOCL library.
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp.
 */

#pragma once


#ifdef SOCL_HPPTEST
namespace snu::hpptest
{
	typedef bool condition_type;

	template <condition_type expr = true>
	consteval inline void must_pass()
	{
		SOCL_HPPTEST_ASSERT(expr);
	}
} // namespace snu::hpptest
#endif
