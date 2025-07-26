/*
 * File: tests/tracked_ptr_test.cc
 * Purpose: Custom smart pointer unit tests in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp all rights reserved.
 */

#include <lib/memory/tracked_ptr.hpp>
#include <gtest/gtest.h>

TEST(TrackedPtrTest, LeakTrackedPtrUsage)
{
	snu::memory::tracked_ptr<int>* ptr = new snu::memory::tracked_ptr<int>(42);
	snu::memory::tracked_ptr<int>* ptr2 = new snu::memory::tracked_ptr<int>(42);
	snu::memory::tracked_ptr<int>* ptr3 = new snu::memory::tracked_ptr<int>(42);

	EXPECT_EQ(snu::memory::tracked_ptr<int>::manager().allocator().allocated_count_, 3);
	ASSERT_TRUE(snu::memory::tracked_ptr<int>::manager().allocator().deallocated_count_ == 0);
}