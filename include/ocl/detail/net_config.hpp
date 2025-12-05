/*
 * File: detail/net_config.hpp
 * Purpose: Network Config file of the OCL.CORE library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef __OCL_NET_CONFIG
#define __OCL_NET_CONFIG

#include <stdexcept>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <cstddef>
#include <cstring>

#ifdef OCL_WINDOWS
#error !!! "Windows is not supported yet for <unique_socket>" !!!
#endif // OCL_WINDOWS

#endif // __OCL_NET_CONFIG