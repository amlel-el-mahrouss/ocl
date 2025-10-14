/*
 * File: tests/tracked_ptr_test.cc
 * Purpose: Custom smart pointer unit tests in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss 
 */

#include <lib/memory/tracked_ptr.hpp>
#include <gtest/gtest.h>

TEST(TrackedPtrTest, BasicTrackedPtrUsage)
{
	scl::memory::tracked_ptr<int> ptr = scl::memory::make_tracked<int>(42);

	ASSERT_TRUE(ptr);
	EXPECT_EQ(*ptr, 42);

	scl::memory::tracked_ptr<int> ptr2;

	scl::memory::swap(ptr, ptr2);

	ptr2.reset();

	EXPECT_EQ(scl::memory::tracked_ptr<int>::manager().allocator().allocated_count_, 1);
}