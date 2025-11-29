/*
 * File: tests/chunk_test.cc
 * Purpose: Chunk unit tests in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#include <io/print.hpp>
#include <gtest/gtest.h>
#include <core/chunk_string.hpp>

const char* test_string = "HELLO, WORLD!\r\n";
const auto	iterations	= 1024000;
const auto	limit		= 30;

TEST(ChunkTest, BasicChunkUsage)
{
	ocl::basic_chunk_string<char, iterations> optimized;
	optimized += test_string;
	
	EXPECT_TRUE(optimized.str() == test_string);
}
