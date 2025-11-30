/*
 * File: tests/fix_test.cc
 * Purpose: Custom FIX protocol tests.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#include <fix/parser.hpp>
#include <gtest/gtest.h>

constexpr const char default_fix[] = {
	'8', '=', 'F', 'I', 'X', '.', '4', '.', '2', 0x01,
	'9', '=', '6', '3', 0x01, // BodyLength = 63
	'3', '5', '=', 'A', 0x01,
	'4', '9', '=', 'S', 'E', 'R', 'V', 'E', 'R', 0x01,
	'5', '6', '=', 'C', 'L', 'I', 'E', 'N', 'T', 0x01,
	'3', '4', '=', '1', '7', '7', 0x01,
	'5', '2', '=', '2', '0', '0', '9', '0', '1', '0', '7', '-', '1', '8', ':', '1', '5', ':', '1', '6', 0x01,
	'9', '8', '=', '0', 0x01,
	'1', '0', '8', '=', '3', '0', 0x01,
	'1', '0', '=', '1', '4', '3', 0x01, 0x00 // CheckSum = 143
};

TEST(FIXTest, BasicFIXUsage)
{
	ocl::fix::basic_visitor<char>	 basic_visitor;
	ocl::fix::basic_range_data<char> fix = basic_visitor.visit(default_fix);

	EXPECT_TRUE(fix.is_valid());
}
