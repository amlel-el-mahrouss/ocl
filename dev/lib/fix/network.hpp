/*
 * File: fix/network.hpp
 * Purpose: Financial Information Exchange in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp.
 */

#ifndef _SNU_FIX_NETWORK_HPP
#define _SNU_FIX_NETWORK_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <utility>
#include <cstddef>

#define SNU_MODEM : protected snu::fix::basic_delivery_modem

namespace snu::fix
{
	class basic_delivery_modem;

	typedef int32_t delivery_socket_type;

	/// @brief a delivery modem is a container which establishes a comm. channel between the FIX session and application.
	class basic_delivery_modem
	{
	public:
		explicit basic_delivery_modem() = default;
		virtual ~basic_delivery_modem()		  = default;

		basic_delivery_modem& operator=(const basic_delivery_modem&) = default;
		basic_delivery_modem(const basic_delivery_modem&)			 = default;

	public:
		static constexpr auto local_address = "127.0.0.1";
		static constexpr auto backlog_count = 18U;

	public:
		delivery_socket_type fd_{};

		template <typename T>
		bool receive(T& out, std::size_t len) noexcept
		{
			static_assert(std::is_pointer<T>::value, "T is not a pointer!");

			if (!out)
				return false;

			if (!len)
				return false;

			auto ret = ::recv(fd_, out, len, MSG_WAITALL);

			return ret > 0;
		}

		template <typename T>
		bool transmit(T& out, std::size_t len) noexcept
		{
			static_assert(std::is_pointer<T>::value, "T is not a pointer!");

			if (!out)
				return false;

			if (!len)
				return false;

			auto ret = ::send(fd_, out, len, 0);

			return ret > 0;
		}

		template <int32_t AF, int32_t Kind, int32_t IPProto, int32_t Port>
		bool construct(const char* addr = basic_delivery_modem::local_address, const bool& is_server = false) noexcept
		{
			static_assert(AF != 0, "AF is zero");
			static_assert(Kind != 0, "Kind is zero");
			static_assert(IPProto != 0, "IPProto is zero");

			fd_ = ::socket(AF, Kind, IPProto);

			if (fd_ < 1)
				return false;

			struct sockaddr_in addr_
			{
			};

			addr_.sin_addr.s_addr = ::inet_addr(addr);
			addr_.sin_port		  = Port;

			if (!is_server)
			{
				auto ret = ::connect(fd_, (struct sockaddr*)&addr_, sizeof(decltype(addr_)));
				return ret == 0;
			}

			::listen(fd_, basic_delivery_modem::backlog_count);

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
} // namespace snu::fix

#endif // ifndef _SNU_FIX_NETWORK_HPP