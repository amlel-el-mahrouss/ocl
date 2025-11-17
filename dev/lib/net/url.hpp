/*
 * File: net/url.hpp
 * Purpose: URL container in modern C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the MIT license.
 */

#pragma once

#include <string>
#include <sstream>

/// @author Amlal El Mahrouss (amlal@nekernel.org)
/// @brief Parse URLs (in a non-standard way).

namespace ocl::net
{
	template <typename char_type>
	class basic_url;

	enum class url_protocol
	{
		invalid = 0,
		http,
		https,
		mailto,
		bad = 0xff,
	};

	/// @brief Basic URL parser container.
	template <typename char_type>
	class basic_url final
	{
		url_protocol					   m_protocol_{url_protocol::invalid};
		std::basic_stringstream<char_type> m_ss_{};

	public:
		explicit basic_url(const std::basic_string<char_type>& protocol)
		{
			if (protocol.starts_with("https://"))
			{
				m_protocol_ = url_protocol::https;
				this->operator/=(protocol.substr(strlen("https://")));
			}
			else if (protocol.starts_with("http://"))
			{
				m_protocol_ = url_protocol::http;
				this->operator/=(protocol.substr(strlen("http://")));
			}
			else if (protocol.starts_with("mailto:"))
			{
				m_protocol_ = url_protocol::mailto;
				this->operator/=(protocol.substr(strlen("mailto:")));
			}
		}

		~basic_url() = default;

		basic_url& operator=(const basic_url&) = default;
		basic_url(const basic_url&)			   = default;

	private:
		basic_url& operator/=(const std::basic_string<char_type>& in)
		{
			if (in.empty())
				return *this;

			m_ss_ += in;
			return *this;
		}

		basic_url& operator/=(const char_type& in)
		{
			m_ss_ += in;
			return *this;
		}

		explicit operator bool()
		{
			return this->is_valid();
		}

	public:
		bool protocol_exists()
		{
			return this->m_protocol_ != url_protocol::bad || this->m_protocol_ != url_protocol::invalid;
		}

		bool is_valid()
		{
			return m_ss_.size() > 0 && this->protocol_exists();
		}
	};
} // namespace ocl::net
