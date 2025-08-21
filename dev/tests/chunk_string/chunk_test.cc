/*
 * File: tests/net_test.cc
 * Purpose: Network unit tests in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp.
 */

#include <lib/io/print.hpp>
#include <lib/tests/gtest.hpp>
#include <lib/utility/chunk_string.hpp>

TEST(ChunkTest, BasicChunkUsage)
{
	const std::string test_string = "HELLO, WORLD!";
	const unsigned iterations = 1024000;

	auto start = std::chrono::high_resolution_clock::now();

	snu::basic_chunk_string<char> optimized;

	for (unsigned i = 0; i < iterations; ++i)
 	{
		optimized += test_string;
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto optimized_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	EXPECT_TRUE(optimized_time.count() < 200U);
}
