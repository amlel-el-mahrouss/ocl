/*
 * File: smart_socket.hpp
 * Purpose: Smart Socket helpers.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, Licensed under the Boost Software License. Licensed under the BSL 1.0 license
 */

#ifndef __OCL_SMART_SOCKET
#define __OCL_SMART_SOCKET

#include <ocl/detail/config.hpp>

#ifndef __OCL_FREESTANDING
#include <boost/asio.hpp>

#ifdef OCL_POSIX
# include <ocl/posix/unique_socket.hpp>
#endif
#endif // !__OCL_FREESTANDING

#endif // __OCL_SMART_SOCKET