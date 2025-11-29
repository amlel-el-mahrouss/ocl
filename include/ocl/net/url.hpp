/*
 * File: net/url.hpp
 * Purpose: URL container in modern C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#pragma once

#include <core/config.hpp>

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
		enum
		{
			invalid = 0,
			http	= 100,
			https,
			file,
			ftp,
			mailto = 200,
			tel,
			bad = 0xff,
		};

	private:
		auto to_string_()
		{
			if (m_protocol_ == https)
				return "https://";

			if (m_protocol_ == http)
				return "http://";

			if (m_protocol_ == file)
				return "file://";

			if (m_protocol_ == tel)
				return "tel:";

			if (m_protocol_ == mailto)
				return "mailto:";

			return "invalid:";
		}

		auto to_enum_(const std::basic_string<char_type>& protocol)
		{
			if (protocol == "https")
				return https;

			if (protocol == "http")
				return http;

			if (protocol == "file")
				return file;

			if (protocol == "tel")
				return tel;

			if (protocol == "mailto")
				return mailto;

			return invalid;
		}

		uint32_t						   m_protocol_{basic_url::invalid};
		std::basic_stringstream<char_type> m_ss_{};
		std::basic_string<char_type>	   m_port_{""};

	public:
		using ref_type = basic_url&;

		explicit basic_url(const uint32_t& protocol)
		{
			m_protocol_ = protocol;
		}

		~basic_url() = default;

		basic_url& operator=(const basic_url&) = default;
		basic_url(const basic_url&)			   = default;

	public:
		ref_type operator/=(const std::basic_string<char_type>& in)
		{
			if (in.empty())
				return *this;

			if (in.starts_with(":"))
			{
				if (m_protocol_ == tel || m_protocol_ == mailto)
					return *this;

				m_port_ = in.substr(1);
			}
			else if (in.starts_with("+"))
			{
				if (m_protocol_ != tel)
					return *this;

				for (auto& ch : in)
				{
					if (ch == ' ')
						return *this;
				}
			}

			m_ss_ << in;

			if (!in.ends_with("/"))
				m_ss_ << "/";

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

		std::basic_string<char_type> assemble() noexcept
		{
			std::basic_string<char_type> out = to_string_();
			out += this->m_ss_.str();

			out.pop_back();

			return out;
		}

		bool is_valid() const noexcept
		{
			return m_ss_.size() > 0 && this->m_protocol_ != basic_url::bad || this->m_protocol_ != basic_url::invalid;
		}
	};

	using url = basic_url<char>;
} // namespace ocl::net
