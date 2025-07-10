/*
* File: fix/netowrk.hpp
 * Purpose: Financial Information Exchange in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp all rights reserved.
 */

#ifndef _SNU_FIX_NETWORK_HPP
#define _SNU_FIX_NETWORK_HPP

#include <arpa/inet.h>
#include <sys/socket.h>

namespace snu::fix
{
	class network_rx;
	class network_tx;
} // namespace snu::fix

#endif // ifndef _SNU_FIX_NETWORK_HPP