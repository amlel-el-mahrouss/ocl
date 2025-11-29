/*
 * File: net/modem.hpp
 * Purpose: Modem concept in modern C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#pragma once

#include <core/config.hpp>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <cstddef>
#include <cstring>

#define OCL_MODEM_INTERFACE : public ocl::net::modem

#ifdef _WIN32
#error !!! "Windows is not supported yet for <modem>" !!!
#endif // _WIN32

namespace ocl::net
{
	class modem;

	/// =============================================================================
	/// @brief Modem container concept, a container to read and write on a network stream.
	/// =============================================================================
	class modem final
	{
	public:
		using socket_type	 = int64_t;
		using error_type	 = bool;
		using condition_type = bool;

	private:
		socket_type	   fd_{};
		condition_type is_server_{false};
		error_type	   bad_{true};

	public:
		const error_type& bad{bad_};

		explicit modem() = default;

		~modem()
		{
			this->destroy();
		}

		modem& operator=(const modem&) = delete;
		modem(const modem&)			   = delete;

		static constexpr auto		local_address_ip4 = "127.0.0.1";
		static constexpr auto		local_address_ip6 = "::1";
		static constexpr const auto backlog_count	  = 5U;

		/// =============================================================================
		/// @brief Check if the modem is valid.
		/// @return true if valid, false otherwise.
		/// =============================================================================

		bool is_valid() const noexcept
		{
			return this->fd_ != -1 && !this->bad_;
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

			if (this->is_server_)
				cl_ = ::accept(fd_, nullptr, nullptr);

			auto ret = ::recv(cl_, out, len, 0);

			return ret > 0L;
		}

		template <typename ptr_type>
		bool transmit(ptr_type& out, std::size_t len) noexcept
		{
			static_assert(std::is_pointer<ptr_type>::value, "ptr_type is not a pointer!");

			if (!out)
				return false;

			if (!len)
				return false;

			auto ret = ::send(fd_, out, len, 0);

			bad_ = !(ret >= 0L);

			return ret >= 0L;
		}

		template <typename char_type>
		bool transmit(const std::basic_string<char_type>& out) noexcept
		{
			if (out.empty())
				return false;

			auto ret = ::send(fd_, out.data(), out.size(), 0);

			bad_ = !(ret >= 0L);

			return ret >= 0L;
		}

		template <int32_t af, int32_t kind, int32_t port>
		bool construct(const char* addr = modem::local_address_ip4, const bool& is_server = false) noexcept
		{
			static_assert(af != 0, "Address family is zero");
			static_assert(kind != 0, "Kind is zero");

			must_pass<af == AF_INET || af == AF_INET6>();
			must_pass<kind == SOCK_STREAM || kind == SOCK_DGRAM>();
			must_pass<(port > 0) && (port < 65536)>();

			fd_		   = ::socket(af, kind, 0);
			is_server_ = is_server;

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

			int ret = ::bind(fd_, (struct sockaddr*)&addr_, sizeof(addr_));

			bad_ = ret == -1;

			::listen(fd_, modem::backlog_count);

			return bad_ == false;
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
