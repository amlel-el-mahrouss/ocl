// Copyright 2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-org/core

/// @brief Checks if the test fails with the expected value.
/// @author Amlal El Mahrouss

#include <ocl/option.hpp>

#define BOOST_TEST_MODULE option
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(option_should_fail)
{
	bool ret = false;
	try
	{
		ocl::option opt(ocl::eval_false());
		opt.expect("");
	}
	catch (...)
	{
		ret = true;
	}
	BOOST_TEST(ret == true);
}

BOOST_AUTO_TEST_CASE(option_should_succeed)
{
	bool ret = true;
	try
	{
		ocl::option opt(ocl::eval_true());
		opt.expect("");
	}
	catch (...)
	{
		ret = false;
	}
	BOOST_TEST(ret == true);
}
