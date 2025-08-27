/*
 * File: net/modem.hpp
 * Purpose: Modem concept in modern C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss 
 */

#ifndef _OCL_NET_NETWORK_HPP
#define _OCL_NET_NETWORK_HPP

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <utility>
#include <cstddef>

#define OCL_MODEM_INTERFACE : protected ocl::net::basic_modem

namespace ocl::net
{
	template <typename char_type>
	class basic_modem;

	typedef int64_t socket_type;

	/// @brief Modem container concept, a container to read and write on a network stream.
	template <typename char_type>
	class basic_modem
	{
		socket_type fd_{};
		bool		server_fd_{};

	public:
		explicit basic_modem() = default;
		virtual ~basic_modem() = default;

		basic_modem& operator=(const basic_modem&) = default;
		basic_modem(const basic_modem&)			   = default;

		static constexpr auto		local_address_ip4 = "127.0.0.1";
		static constexpr auto		local_address_ip6 = "::1";
		static constexpr const auto backlog_count	  = 5U;

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

			socket_type cl_{fd_};

			if (this->server_fd_)
				cl_ = ::accept(fd_, nullptr, nullptr);

			auto ret = ::recv(cl_, out, len, 0);

			return ret > 0L;
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

			return ret > 0L;
		}

		template <typename ptr_type>
		bool transmit(std::basic_string<ptr_type> out) noexcept
		{
			if (out.empty())
				return false;

			auto ret = ::send(fd_, out.data(), out.size(), 0);

			return ret > 0L;
		}

		template <int32_t af, int32_t kind, int32_t port>
		bool construct(const char* addr = basic_modem::local_address_ip4, const bool& is_server = false) noexcept
		{
			static_assert(af != 0, "Address family is zero");
			static_assert(kind != 0, "Kind is zero");

			fd_		   = ::socket(af, kind, 0);
			server_fd_ = is_server;

			if (fd_ == -1)
				return false;

			struct sockaddr_in addr_;
			std::memset(&addr_, 0, sizeof(struct sockaddr_in));

			addr_.sin_addr.s_addr = ::inet_addr(addr);
			addr_.sin_port		  = htons(port);
			addr_.sin_family	  = af;

			if (!is_server)
			{
				const auto ret = ::connect(fd_, reinterpret_cast<struct sockaddr*>(&addr_), sizeof(addr_));
				return ret == 0L;
			}

			::bind(fd_, (struct sockaddr*)&addr_, sizeof(addr_));
			::listen(fd_, basic_modem::backlog_count);

			return true;
		}

		bool destroy() noexcept
		{
			if (!fd_)
				return false;

			::shutdown(fd_, SHUT_RDWR);
			::close(fd_);

			fd_ = 0L;

			return true;
		}
	};
} // namespace ocl::net

#endif // ifndef _OCL_NET_NETWORK_HPP
