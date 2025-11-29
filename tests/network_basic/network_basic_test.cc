/*
 * File: tests/net_test.cc
 * Purpose: Network unit tests in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#include <net/modem.hpp>
#include <io/print.hpp>
#include <gtest/gtest.h>

/// @brief Basic Send Test 
TEST(NetworkTest, BasicNetworkTransmit)
{
	ocl::net::modem modem;
	modem.construct<AF_INET, SOCK_STREAM, 8000>(ocl::net::modem::local_address_ip4, true);

	EXPECT_TRUE(modem.is_valid());

	std::basic_string<char> buf_dst = "HELLO, WORLD!";
	EXPECT_TRUE(modem.transmit(buf_dst));
}

/// @brief Basic Receive test
TEST(NetworkTest, BasicNetworkReceive)
{
	ocl::net::modem modem;
	modem.construct<AF_INET, SOCK_STREAM, 8000>(ocl::net::modem::local_address_ip4, true);

	EXPECT_TRUE(modem.is_valid());

	std::basic_string<char> buf_dst;
	buf_dst.reserve(512);

	auto buf = buf_dst.data();
	auto sz = buf_dst.size();

	EXPECT_FALSE(modem.receive(buf, sz));
}
