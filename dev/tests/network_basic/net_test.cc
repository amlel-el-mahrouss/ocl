/*
 * File: tests/net_test.cc
 * Purpose: Network unit tests in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp.
 */

#include <lib/net/network.hpp>
#include <lib/io/print.hpp>
#include <cstring>
#include <gtest/gtest.h>

TEST(NetworkTest, BasicNetworkUsage)
{
	snu::net::basic_modem<char> modem;
	modem.construct<AF_INET, SOCK_STREAM, IPPROTO_IP, 80>(snu::net::basic_modem<char>::local_address_ip4, true);

	snu::net::basic_modem<char> modem_cl;
	modem_cl.construct<AF_INET, SOCK_STREAM, IPPROTO_IP, 80>(snu::net::basic_modem<char>::local_address_ip4, false);

	EXPECT_TRUE(modem_cl.is_valid());
	EXPECT_TRUE(modem.is_valid());

	std::basic_string<char> buf_dst = "HELLO, NET!";
	char*					buf		= new char[buf_dst.size()];

	modem_cl.transmit(buf_dst);
	modem.receive<char*>(buf, buf_dst.size());

	snu::io::println<>(buf);
	snu::io::println<>(buf_dst);

	delete[] buf;
	buf = nullptr;
}
