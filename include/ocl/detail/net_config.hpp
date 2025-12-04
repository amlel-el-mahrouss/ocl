/*
 * File: detail/net_config.hpp
 * Purpose: Network Config file of the OCL.CORE library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */
 
#pragma once

#include <stdexcept>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <cstddef>
#include <cstring>

#ifdef OCL_WINDOWS
#error !!! "Windows is not supported yet for <unique_socket>" !!!
#endif // OCL_WINDOWS
