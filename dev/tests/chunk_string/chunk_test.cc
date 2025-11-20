/*
 * File: tests/chunk_test.cc
 * Purpose: Chunk unit tests in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the MIT license.
 */

#include <lib/io/print.hpp>
#include <lib/tests/gtest.hpp>
#include <lib/core/chunk_string.hpp>

TEST(ChunkTest, BasicChunkUsage)
{
	const char* test_string = "HELLO, WORLD!\r\n";
	const auto iterations = 1024000;
	const auto limit = 30;

	auto start = std::chrono::high_resolution_clock::now();

	ocl::basic_chunk_string<char, iterations> optimized;

	for (unsigned i = 0; i < iterations; ++i)
 	{
		optimized += test_string;
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto optimized_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	EXPECT_TRUE(optimized_time.count() < 100U);
}
