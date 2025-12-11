/*
 * File: unique_socket.hpp
 * Purpose: RAII socket concept in modern C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef __OCL_CORE_SOCKET
#define __OCL_CORE_SOCKET

#include <ocl/detail/config.hpp>
#include <ocl/detail/posix/net_config.hpp>

namespace ocl
{
	class unique_socket;

	inline constexpr auto socket_null = 0;

	class unique_socket final
	{
	public:
		using socket_type	 = int;
		using error_type	 = bool;
		using condition_type = bool;
		using socket_state	 = int;

	private:
		socket_type	   socket_{};
		condition_type is_server_{false};
		error_type	   bad_{false};

	public:
		unique_socket() = default;

		~unique_socket()
		{
			this->destroy();
		}

		unique_socket& operator=(const unique_socket&) = delete;
		unique_socket(const unique_socket&)			   = delete;

		unique_socket& operator=(unique_socket&& other) noexcept
		{
			if (this != &other)
			{
				this->destroy();

				socket_	   = other.socket_;
				is_server_ = other.is_server_;
				bad_	   = other.bad_;

				other.socket_ = 0;
				other.bad_	  = true;
			}

			return *this;
		}

		unique_socket(unique_socket&& other) noexcept
			: socket_(other.socket_), is_server_(other.is_server_), bad_(other.bad_)
		{
			other.socket_ = 0;
			other.bad_	  = true;
		}

		static constexpr auto any_address	= "0.0.0.0";
		static constexpr auto backlog_count = 20U;

		const error_type& bad()
		{
			return bad_;
		}

		unique_socket::socket_state state() noexcept
		{
			socket_state error = 0;
			socklen_t	 len   = sizeof(error);
			getsockopt(socket_, SOL_SOCKET, SO_ERROR, &error, &len);

			return error;
		}

		unique_socket accept() noexcept
		{
			socket_type cl_{-1};

			if (this->is_server_)
				cl_ = ::accept(socket_, nullptr, nullptr);

			unique_socket ret_sock;
			ret_sock.socket_ = cl_;

			return std::move(ret_sock);
		}

		unique_socket read_server_buffer(char* in, std::size_t len)
		{
			if (!in || !len)
				return {};

			if (!is_server_)
				return {};

			auto ret_sock = accept();

			if (ret_sock.socket_ == -1)
				throw std::invalid_argument("no connection to accept.");

			auto ret	  = ::recv(ret_sock.socket_, in, len, 0);
			ret_sock.bad_ = ret < 0L;

			return ret_sock;
		}

		void read_client_buffer(char* in, std::size_t len)
		{
			if (!in || !len)
				return;

			if (is_server_)
				return;

			auto ret   = ::recv(this->socket_, in, len, 0);
			this->bad_ = ret < 0L;
		}

		void write_from_buffer(const char* out, std::size_t len)
		{
			if (!out)
				return;

			if (!len)
				return;

			auto ret   = ::send(this->socket_, out, len, 0);
			this->bad_ = ret < 0L;
		}

		template <uint16_t port>
		static unique_socket make_socket(const std::string& address, const bool is_server)
		{
			if (unique_socket sock; sock.construct<AF_INET, SOCK_STREAM, port>(address.c_str(), is_server))
				return sock;

			throw std::invalid_argument("invalid socket argument");
		}

	private:
		template <uint16_t af, uint16_t kind, uint16_t port>
		bool construct(const char* addr = unique_socket::any_address, const bool& is_server = false) noexcept
		{
			static_assert(af != 0, "Address family is zero");
			static_assert(kind != 0, "Kind is zero");

			socket_	   = ::socket(af, kind, 0);
			is_server_ = is_server;

			if (socket_ == -1)
				return false;

			struct sockaddr_in addr_;
			std::memset(&addr_, 0, sizeof(struct sockaddr_in));

			if (addr == unique_socket::any_address)
				addr_.sin_addr.s_addr = INADDR_ANY;
			else
				addr_.sin_addr.s_addr = ::inet_addr(addr);

			addr_.sin_port	 = htons(port);
			addr_.sin_family = af;

			if (!is_server)
			{
				const auto ret = ::connect(socket_, reinterpret_cast<struct sockaddr*>(&addr_), sizeof(addr_));
				bad_		   = ret == -1;
				return bad_ == false;
			}

			int ret = ::bind(socket_, (struct sockaddr*)&addr_, sizeof(addr_));

			bad_ = ret == -1;

			if (bad_)
				return false;

			ret = ::listen(socket_, unique_socket::backlog_count);

			bad_ = ret == -1;

			return bad_ == false;
		}

		bool destroy() noexcept
		{
			if (!socket_)
				return false;

			::close(socket_);

			socket_ = 0L;

			return true;
		}
	};

	template <typename TS>
	concept IsValidSocket = requires(TS& sock) {
		{ !sock.bad() };
	};
} // namespace ocl

#endif