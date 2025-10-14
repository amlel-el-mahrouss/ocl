/*
 * File: net/url.hpp
 * Purpose: URL container in modern C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss 
 */

#pragma once

#include <string>
#include <iostream>
#include <sstream>

/// @author Amlal El Mahrouss (amlal@nekernel.org)

namespace scl::net
{
	template <typename char_type>
	class basic_url;

	template <typename char_type>
	class basic_url_traits;

	/// @brief Basic URL parser container.
	template <typename char_type>
	class basic_url final
	{
		friend basic_url_traits<char_type>;

		std::basic_stringstream<char_type> ss_{};

	public:
		explicit basic_url() = default;
		~basic_url()		 = default;

		basic_url& operator=(const basic_url&) = default;
		basic_url(const basic_url&)			   = default;

		basic_url& operator/=(const std::basic_string<char_type>& in)
		{
			if (in.empty())
				return *this;

			ss_ += in;
			return *this;
		}

		basic_url& operator/=(const char_type& in)
		{
			ss_ += in;
			return *this;
		}

		explicit operator bool()
		{
			return this->is_valid();
		}

		bool is_valid()
		{
			return ss_.size() > 0;
		}
	};

	enum class protocol
	{
		http,
		https,
		mailto,
		bad
	};
} // namespace scl::net
