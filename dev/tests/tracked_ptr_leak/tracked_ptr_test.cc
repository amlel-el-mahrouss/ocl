/*
 * File: tests/tracked_ptr_test.cc
 * Purpose: Custom smart pointer unit tests in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss 
 */

#include <lib/memory/tracked_ptr.hpp>
#include <gtest/gtest.h>

TEST(TrackedPtrTest, LeakTrackedPtrUsage)
{
	ocl::memory::tracked_ptr<int>* ptr = new ocl::memory::tracked_ptr<int>(42);
	ocl::memory::tracked_ptr<int>* ptr2 = new ocl::memory::tracked_ptr<int>(42);
	ocl::memory::tracked_ptr<int>* ptr3 = new ocl::memory::tracked_ptr<int>(42);

	EXPECT_EQ(ocl::memory::tracked_ptr<int>::manager().allocator().allocated_count_, 3);
	ASSERT_TRUE(ocl::memory::tracked_ptr<int>::manager().allocator().deallocated_count_ == 0);
}