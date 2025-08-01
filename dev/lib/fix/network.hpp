/*
 * File: fix/network.hpp
 * Purpose: Financial Information Exchange in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp all rights reserved.
 */

#ifndef _SNU_FIX_NETWORK_HPP
#define _SNU_FIX_NETWORK_HPP

#include <arpa/inet.h>
#include <sys/socket.h>

#include <cstddef>

namespace snu::fix
{
	class delivery_modem;

	typedef int32_t delivery_socket_type;

	/// @brief a delivery modem is a container which establishes a comm. channel between the FIX session and application.
	class delivery_modem final
	{
	public:
		explicit delivery_modem() = default;
		~delivery_modem()		  = default;

		delivery_modem& operator=(const delivery_modem&) = default;
		delivery_modem(const delivery_modem&)			 = default;

	public:
		delivery_socket_type fd_{};

		template <typename T>
		bool receive(T& out, std::size_t len) noexcept
		{
			if (!len)
				return false;

			auto ret = ::recv(fd_, &out, len, 0);
			return ret > 0;
		}

		template <typename T>
		bool transmit(T& out, std::size_t len) noexcept
		{
			if (!out)
				return false;
			if (!len)
				return false;

			auto ret = ::send(fd_, out, len, 0);
			return ret > 0;
		}

		bool construct() noexcept
		{
			fd_ = ::socket(SOCK_STREAM, AF_INET, 0);
			return fd_ > 0;
		}

		bool destroy() noexcept
		{
			if (!fd_)
				return false;

			::shutdown(fd_, SHUT_RDWR);

			fd_ = 0U;

			return true;
		}
	};
} // namespace snu::fix

#endif // ifndef _SNU_FIX_NETWORK_HPP