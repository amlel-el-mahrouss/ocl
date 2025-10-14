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
	scl::memory::tracked_ptr<int>* ptr = new scl::memory::tracked_ptr<int>(42);
	scl::memory::tracked_ptr<int>* ptr2 = new scl::memory::tracked_ptr<int>(42);
	scl::memory::tracked_ptr<int>* ptr3 = new scl::memory::tracked_ptr<int>(42);

	EXPECT_EQ(scl::memory::tracked_ptr<int>::manager().allocator().allocated_count_, 3);
	ASSERT_TRUE(scl::memory::tracked_ptr<int>::manager().allocator().deallocated_count_ == 0);
}