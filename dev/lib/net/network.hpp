/*
 * File: net/network.hpp
 * Purpose: Modem concept in modern C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp.
 */

#ifndef _SNU_NET_NETWORK_HPP
#define _SNU_NET_NETWORK_HPP

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <utility>
#include <cstddef>

#define SNU_MODEM_INTERFACE : protected snu::net::basic_modem

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

		static constexpr auto local_address_ip6 = "127.0.0.1";
		static constexpr auto local_address_ip4 = "::1";
		
		static constexpr auto backlog_count		= 18U;

		socket_type fd_{};

		bool is_valid() const noexcept
		{
			return this->fd_ != -1;
		}

		template <typename ptr_type>
		bool receive(ptr_type& out, std::size_t len) noexcept
		{
			static_assert(std::is_pointer<ptr_type>::value, "ptr_type is not a pointer!");

			if (!out)
				return false;

			if (!len)
				return false;

			auto ret = ::recv(fd_, out, len, MSG_WAITALL);

			return ret > 0;
		}

		template <typename ptr_type>
		bool transmit(ptr_type& out, std::size_t len) noexcept
		{
			static_assert(std::is_pointer<ptr_type>::value, "char_type is not a pointer!");

			if (!out)
				return false;

			if (!len)
				return false;

			auto ret = ::send(fd_, out, len, 0);

			return ret > 0;
		}

		template <int32_t af, int32_t kind, int32_t ip_proto, int32_t port>
		bool construct(const char* addr = basic_modem::local_address_ip4, const bool& is_server = false) noexcept
		{
			static_assert(af != 0, "AF is zero");
			static_assert(kind != 0, "Kind is zero");
			static_assert(ip_proto != 0, "IPProto is zero");

			fd_ = ::socket(af, kind, ip_proto);

			if (fd_ == -1)
				return false;

			struct sockaddr_in addr_
			{
			};

			addr_.sin_addr.s_addr = ::inet_addr(addr);
			addr_.sin_port		  = port;

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
			::close(fd_);

			fd_ = 0U;

			return true;
		}
	};
} // namespace snu::net

#endif // ifndef _SNU_NET_NETWORK_HPP
