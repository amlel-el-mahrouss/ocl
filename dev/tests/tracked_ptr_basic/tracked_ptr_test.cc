/*
 * File: tests/tracked_ptr_test.cc
 * Purpose: Custom smart pointer unit tests in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#include <lib/memory/tracked_ptr.hpp>
#include <lib/tests/gtest.hpp>

TEST(TrackedPtrTest, BasicTrackedPtrUsage)
{
	ocl::memory::tracked_ptr<int> ptr = ocl::memory::make_tracked<int>(42);

	ASSERT_TRUE(ptr);
	EXPECT_EQ(*ptr, 42);

	ocl::memory::tracked_ptr<int> ptr2;

	ocl::memory::swap(ptr, ptr2);

	ptr2.reset();

	EXPECT_EQ(ocl::memory::tracked_ptr<int>::manager().allocator().allocated_count_, 1);
}