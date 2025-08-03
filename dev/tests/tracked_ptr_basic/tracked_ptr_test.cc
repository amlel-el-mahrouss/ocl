/*
 * File: tests/tracked_ptr_test.cc
 * Purpose: Custom smart pointer unit tests in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp.
 */

#include <lib/memory/tracked_ptr.hpp>
#include <gtest/gtest.h>

TEST(TrackedPtrTest, BasicTrackedPtrUsage)
{
	snu::memory::tracked_ptr<int> ptr = snu::memory::make_tracked<int>(42);

	ASSERT_TRUE(ptr);
	EXPECT_EQ(*ptr, 42);

	snu::memory::tracked_ptr<int> ptr2;

	snu::memory::swap(ptr, ptr2);

	ptr2.reset();

	EXPECT_EQ(snu::memory::tracked_ptr<int>::manager().allocator().allocated_count_, 1);
}