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
	ocl::fix::basic_visitor<char>	 basic_visitor;
	ocl::fix::basic_range_data<char> fix = basic_visitor.visit("8=FIX.4.2|9=65|35=A|49=SERVER|56=CLIENT|34=177|52=20090107-18:15:16|98=0|108=30|10=062|");

	EXPECT_EQ(fix.magic_, ocl::fix::detail::begin_fix());
	EXPECT_TRUE(fix.is_valid());
}
