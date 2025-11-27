/*
 * File: net/url.hpp
 * Purpose: URL container in modern C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#pragma once

#include <string>
#include <sstream>

/// @author Amlal El Mahrouss (amlal@nekernel.org)
/// @brief Parse URIs/URLs/URNs (Non rfc3986 compliant.)

namespace ocl::net
{
	template <typename char_type>
	class basic_url;

	/// @brief Basic URL parser container.
	template <typename char_type>
	class basic_url final
	{
	public:
		using reference = basic_url&;

		enum
		{
			invalid = 0,
			http,
			https,
			mailto,
			ftp,
			tel,
			bad = 0xff,
		};

		uint32_t						   m_protocol_{basic_url::invalid};
		std::basic_stringstream<char_type> m_ss_{};
		std::basic_string<char_type>	   m_port_{""};

	public:
		explicit basic_url(const std::basic_string<char_type>& protocol)
		{
			if (protocol.starts_with("https://"))
			{
				m_protocol_ = basic_url::https;
				this->operator/=(protocol.substr(std::size("https://")));
			}
			else if (protocol.starts_with("http://"))
			{
				m_protocol_ = basic_url::http;
				this->operator/=(protocol.substr(std::size("http://")));
			}
			else if (protocol.starts_with("mailto:"))
			{
				m_protocol_ = basic_url::mailto;
				this->operator/=(protocol.substr(std::size("mailto:")));
			}
			else if (protocol.starts_with("tel:"))
			{
				m_protocol_ = basic_url::tel;
				this->operator/=(protocol.substr(std::size("tel:")));
			}
			else if (protocol.starts_with("ftp:"))
			{
				m_protocol_ = basic_url::ftp;
				this->operator/=(protocol.substr(std::size("ftp:")));
			}
		}

		~basic_url() = default;

		basic_url& operator=(const basic_url&) = default;
		basic_url(const basic_url&)			   = default;

	private:
		reference operator/=(const std::basic_string<char_type>& in)
		{
			if (in.empty())
				return *this;

			if (in.starts_with(":"))
			{
				m_port_ = in.substr(1);
				return *this;
			}

			m_ss_ += in;
			return *this;
		}

		reference operator/=(const char_type& in)
		{
			m_ss_ += in;
			return *this;
		}

		explicit operator bool()
		{
			return this->is_valid();
		}

	public:
		uint32_t protocol() const noexcept
		{
			return this->m_protocol_;
		}

		std::basic_string<char_type> port() const noexcept
		{
			return this->m_port_;
		}

		bool is_valid() const noexcept
		{
			return m_ss_.size() > 0 && this->m_protocol_ != basic_url::bad || this->m_protocol_ != basic_url::invalid;
		}
	};

	using url = basic_url<char>;
} // namespace ocl::net
