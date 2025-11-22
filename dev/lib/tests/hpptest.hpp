/*
 * File: tests/hpptest.hpp
 * Purpose: HPP Test wrapper for the OCL library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#pragma once

#include <lib/io/print.hpp>
#include <cstdlib>

namespace ocl::hpptest
{
	/// @brief Standard termination error handler, called when a test fails.
	struct standard_terminate final
	{
		template <bool stop_execution = true>
		static void error() noexcept
		{
			ocl::io::print("standard_terminate::error, terminating...\n");

			if (stop_execution)
				std::terminate();
		}
	};

	struct posix_terminate final
	{
		template <bool stop_execution = true, errno_t args>
		static void error(errno_t err) noexcept
		{
			ocl::io::print("posix_terminate::error: expected=", strerror(args), ", got=", strerror(err), "\n");

			if (stop_execution)
				std::terminate();
		}
	};

	typedef bool condition_type;

	template <condition_type expr = true>
	consteval inline void must_pass()
	{
#ifdef OCL_HPPTEST
		OCL_HPPTEST_ASSERT(expr);
#endif // _WIN32
	}

	template <condition_type expect, typename on_fail>
	inline void must_pass(condition_type cond) noexcept
	{
		if (cond != expect)
		{
			on_fail::template error<true>();
		}
	}

	template <errno_t expect = 0>
	inline void must_pass(errno_t ern) noexcept
	{
		if (ern != expect)
		{
			posix_terminate::error<true, expect>(ern);
		}
	}

#ifdef _WIN32
	struct win32_terminate final
	{
		template <bool stop_execution = false>
		static void error(HRESULT err) noexcept
		{
			ocl::io::print("win32_terminate::error: expected=S_OK, got=", err, "\n");

			if (stop_execution)
				std::terminate();
		}
	};

	template <HRESULT expect = S_OK>
	inline void must_pass(HRESULT hr) noexcept
	{
		if (hr != expect)
		{
			win32_terminate::error<true>(hr);
		}
	}
#endif // _WIN32
} // namespace ocl::hpptest
