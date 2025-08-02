/*
 * File: tests/tracked_ptr_test.cc
 * Purpose: Custom smart pointer unit tests in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp all rights reserved.
 */

#include <lib/fix/parser.hpp>
#include <gtest/gtest.h>

TEST(FIXTest, BasicFIXUsage)
{
	snu::fix::basic_visitor<char>	 basic_visitor;
	snu::fix::basic_range_data<char> fix = basic_visitor.visit("8=FIX.4.2|9=65|35=A|49=SERVER|56=CLIENT|34=177|52=20090107-18:15:16|98=0|108=30|10=062|");

	EXPECT_EQ(fix.magic_, "FIX.4.2");
	EXPECT_TRUE(fix.is_valid());
}