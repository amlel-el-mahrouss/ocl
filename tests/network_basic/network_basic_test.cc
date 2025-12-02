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
TEST(NetworkTest, BasicNetworkReceive1)
{
	ocl::net::unique_socket sock = ocl::net::unique_socket::make_socket<8000>(ocl::net::unique_socket::local_address_ip4, false);
	std::basic_string<char> buf_dst = "HELLO, WORLD!";
	EXPECT_TRUE(sock.read_server_buffer(buf_dst.data(), buf_dst.size()).bad() == false);
}

/// @brief Basic Receive test
TEST(NetworkTest, BasicNetworkReceive2)
{
	ocl::net::unique_socket sock = ocl::net::unique_socket::make_socket<8000>(ocl::net::unique_socket::local_address_ip4, true);

	EXPECT_TRUE(!sock.bad());

	std::basic_string<char> buf_dst;
	buf_dst.reserve(512);

	auto buf = buf_dst.data();
	auto sz = buf_dst.size();

	EXPECT_FALSE(!sock.read_server_buffer(buf, sz).bad());
}

TEST(NetworkTest, BasicNetworkConstruct)
{
	auto socket = ocl::net::unique_socket::make_socket<8000>(ocl::net::unique_socket::local_address_ip4, true);
	EXPECT_TRUE(!socket.bad());
}