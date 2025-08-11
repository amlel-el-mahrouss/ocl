/*
 * File: net/network.hpp
 * Purpose: Modem concept in modern C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp.
 */

#ifndef _SNU_NET_NETWORK_HPP
#define _SNU_NET_NETWORK_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <utility>
#include <cstddef>

#define SNU_MODEM_INTERFACE : protected snu::net::basic_delivery_modem

namespace snu::net
{
	template <typename char_type>
	class basic_modem;

	typedef int64_t socket_type;

	/// @brief Delivery modem concept, a container to read and write on a network stream.
	template <typename char_type>
	class basic_modem
	{
	public:
		explicit basic_modem() = default;
		virtual ~basic_modem() = default;

		basic_modem& operator=(const basic_modem&) = default;
		basic_modem(const basic_modem&)			   = default;

		static constexpr auto local_address = "127.0.0.1";
		static constexpr auto backlog_count = 18U;

		socket_type fd_{};

		bool is_valid() const noexcept
		{
			return this->fd_ != -1;
		}

		bool receive(char_type& out, std::size_t len) noexcept
		{
			static_assert(std::is_pointer<char_type>::value, "char_type is not a pointer!");

			if (!out)
				return false;

			if (!len)
				return false;

			auto ret = ::recv(fd_, out, len, MSG_WAITALL);

			return ret > 0;
		}

		bool transmit(char_type& out, std::size_t len) noexcept
		{
			static_assert(std::is_pointer<char_type>::value, "char_type is not a pointer!");

			if (!out)
				return false;

			if (!len)
				return false;

			auto ret = ::send(fd_, out, len, 0);

			return ret > 0;
		}

		template <int32_t AF, int32_t Kind, int32_t IPProto, int32_t Port>
		bool construct(const char* addr = basic_modem::local_address, const bool& is_server = false) noexcept
		{
			static_assert(AF != 0, "AF is zero");
			static_assert(Kind != 0, "Kind is zero");
			static_assert(IPProto != 0, "IPProto is zero");

			fd_ = ::socket(AF, Kind, IPProto);

			if (fd_ == -1)
				return false;

			struct sockaddr_in addr_
			{
			};

			addr_.sin_addr.s_addr = ::inet_addr(addr);
			addr_.sin_port		  = Port;

			if (!is_server)
			{
				const auto ret = ::connect(fd_, reinterpret_cast<struct sockaddr*>(&addr_), sizeof(decltype(addr_)));
				return ret == 0;
			}

			::listen(fd_, basic_modem::backlog_count);

			return true;
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
} // namespace snu::net

#endif // ifndef _SNU_NET_NETWORK_HPP