/*
 * File: tests/network_basic_test.cc
 * Purpose: Network unit tests in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#include <ocl/posix/unique_socket.hpp>
#include <ocl/print.hpp>
#include <gtest/gtest.h>

/// @brief Basic Send test
TEST(NetworkTest, BasicNetworkIO)
{
	ocl::unique_socket sock = ocl::unique_socket::make_socket<8000>(ocl::unique_socket::any_address, true);

	std::vector<char> buf_dst(512);

	buf_dst.push_back('H');
	buf_dst.push_back('e');
	buf_dst.push_back('l');
	buf_dst.push_back('l');
	buf_dst.push_back('o');
	buf_dst.push_back('\0');

	auto buf = buf_dst.data();
	auto sz = buf_dst.size();

	ocl::unique_socket sock2 = ocl::unique_socket::make_socket<8000>(ocl::unique_socket::any_address, false);

	auto accepeted = sock.accept();
	accepeted.write_from_buffer(buf, sz);

	std::vector<char> buf_dst2(512);

	buf = buf_dst2.data();
	sz = buf_dst2.size();

	sock2.read_client_buffer(buf, sz);

	EXPECT_TRUE(!sock.bad());
	EXPECT_TRUE(!sock2.bad());
}

TEST(NetworkTest, BasicNetworkMakeSocket)
{
	auto socket = ocl::unique_socket::make_socket<8000>(ocl::unique_socket::any_address, true);
	EXPECT_TRUE(!socket.bad());
}
