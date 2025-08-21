/*
 * File: tests/net_test.cc
 * Purpose: Network unit tests in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp.
 */

#include <lib/net/modem.hpp>
#include <lib/io/print.hpp>
#include <lib/tests/gtest.hpp>
#include <cstring>

TEST(NetworkTest, BasicNetworkUsage)
{
	snu::net::basic_modem<char> modem;
	modem.construct<AF_INET, SOCK_STREAM, 8000>(snu::net::basic_modem<char>::local_address_ip4, true);

	EXPECT_TRUE(modem.is_valid());

	std::basic_string<char> buf_dst = "HELLO, NET!";
	EXPECT_TRUE(modem.transmit(buf_dst));
}
