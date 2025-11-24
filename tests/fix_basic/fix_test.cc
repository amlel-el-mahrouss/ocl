/*
 * File: tests/fix_test.cc
 * Purpose: Custom FIX protocol tests.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#include <fix/fix.hpp>
#include <tests/hpptest.hpp>
#include <tests/gtest.hpp>

TEST(FIXTest, BasicFIXUsage)
{
	constexpr auto default_fix = "8=FIX.4.2\x01 9=65\x01 35=A\x01 49=SERVER\x01 56=CLIENT\x01 34=177\x01 52=20090107-18:15:16\x01 98=0\x01 108=30\x01 10=062\x01";

	ocl::fix::basic_visitor<char>	 basic_visitor;
	ocl::fix::basic_range_data<char> fix = basic_visitor.visit(default_fix);

	EXPECT_EQ(fix.magic_, ocl::fix::detail::begin_fix());
	EXPECT_TRUE(fix.is_valid());
}
