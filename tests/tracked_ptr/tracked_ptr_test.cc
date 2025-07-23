/*
 * File: tests/tracked_ptr_test.cc
 * Purpose: Custom smart pointer unit tests in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp all rights reserved.
 */

#include <lib/memory/tracked_ptr.hpp>
#include <gtest/gtest.h>

TEST(TrackedPtrTest, BasicTrackedPtrUsage) {
    snu::memory::tracked_ptr<int> ptr = snu::memory::make_tracked<int>(42);
    
    ASSERT_TRUE(ptr);
    EXPECT_EQ(*ptr, 42);

    snu::memory::tracked_ptr<int> ptr2 = std::move(ptr);

    ASSERT_FALSE(ptr);
    ASSERT_TRUE(ptr2);
    
    EXPECT_EQ(*ptr2, 42);

    ptr2.reset();
    ASSERT_FALSE(ptr2);
}