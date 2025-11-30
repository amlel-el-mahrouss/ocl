/*
 * File: tests/net_test.cc
 * Purpose: Network unit tests in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#include <net/unique_socket.hpp>
#include <io/print.hpp>
#include <gtest/gtest.h>

/// @brief Basic Send Test 
TEST(NetworkTest, BasicNetworkTransmit)
{
	ocl::net::unique_socket sock;
	sock.construct<AF_INET, SOCK_STREAM, 8000>(ocl::net::unique_socket::local_address_ip4, true);

	EXPECT_TRUE(sock.is_valid());

	std::basic_string<char> buf_dst = "HELLO, WORLD!";
	EXPECT_TRUE(sock.transmit(buf_dst));
}

/// @brief Basic Receive test
TEST(NetworkTest, BasicNetworkReceive)
{
	ocl::net::unique_socket sock;
	sock.construct<AF_INET, SOCK_STREAM, 8000>(ocl::net::unique_socket::local_address_ip4, true);

	EXPECT_TRUE(sock.is_valid());

	std::basic_string<char> buf_dst;
	buf_dst.reserve(512);

	auto buf = buf_dst.data();
	auto sz = buf_dst.size();

	EXPECT_FALSE(sock.receive(buf, sz));
}

TEST(NetworkTest, BasicNetworkConstruct)
{
	auto socket = ocl::net::make_socket<char, 8000>(ocl::net::unique_socket::local_address_ip4, true);

	EXPECT_TRUE(socket.is_valid());
}