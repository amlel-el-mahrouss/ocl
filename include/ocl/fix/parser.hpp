/*
 * File: fix/parser.hpp
 * Purpose: Financial Information Exchange parser in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef _OCL_FIX_PARSER_HPP
#define _OCL_FIX_PARSER_HPP

#include <core/config.hpp>
#include <hashing/crc_hash.hpp>
#include <io/print.hpp>
#include <algorithm>
#include <string>
#include <vector>

namespace ocl::fix
{
	class basic_visitor;

	struct basic_range;

	class basic_range_data;

	/// @brief Buffer+Length structure
	using range_ptr_t = basic_range*;

	namespace detail
	{
		inline const char* begin_fix() noexcept
		{
			return "FIX.4.2";
		}
	} // namespace detail

	struct basic_range final
	{
		char*  bytes_{nullptr};
		size_t length_{};

		bool is_valid() noexcept
		{
			return this->bytes_ && this->length_ > 0;
		}

		explicit operator bool()
		{
			return this->is_valid();
		}
	};

	/// @brief Convert basic_range to usable string.
	/// @note This function assumes that the basic_range is valid and contains ASCII bytes.
	inline std::string to_string(basic_range& basic_range) noexcept
	{
		if (basic_range.length_ < 1)
			return std::string{};

		return std::string(basic_range.bytes_, basic_range.length_);
	}

	/// @brief a basic_range object containing the FIX packet values.
	class basic_range_data final
	{
	public:
		std::size_t					 magic_len_{};
		std::string					 magic_{};
		string_hash_map<std::string> message_{};

		static inline const char* begin = detail::begin_fix();

		explicit basic_range_data() = default;
		~basic_range_data()			= default;

		basic_range_data& operator=(const basic_range_data&) = default;
		basic_range_data(const basic_range_data&)			 = default;

		std::string operator[](const std::string& key)
		{
			if (key.empty())
				return std::string{};

			auto it = message_.find(key);
			if (it != message_.end())
				return it->second;

			return std::string{};
		}

		bool is_valid()
		{
			return this->operator[]("8").empty() == false;
		}

		explicit operator bool()
		{
			return this->is_valid();
		}
	};

	/// @brief basic_visitor object which returns a fix::basic_range_data instance.
	class basic_visitor final
	{
	public:
		/// AMLALE: Yeah...
		static constexpr const int	soh	 = '\x01';
		static constexpr const char eq	 = '=';
		static constexpr uint32_t	base = 10U;

		explicit basic_visitor() = default;
		~basic_visitor()		 = default;

		basic_visitor& operator=(const basic_visitor&) = default;
		basic_visitor(const basic_visitor&)			   = default;

		basic_range_data operator()(const std::string& in)
		{
			return this->visit(in);
		}

		/// @brief Visit a FIX message and parse it into a basic_range_data object.
		/// @param in The input FIX message as a string.
		/// @warning This function may throw exceptions.
		basic_range_data visit(const std::string& in)
		{
			basic_range_data ret{};

			if (in.empty())
				return ret;

			std::string key;

			std::size_t off = 0UL;

			while (off < in.size())
			{
				// Find the '=' separator
				std::size_t eq_pos = in.find(eq, off);
				if (eq_pos == std::string::npos)
					break;

				// Extract tag (everything from current position to '=')
				std::string tag = in.substr(off, eq_pos - off);

				// Find the SOH delimiter after the value (or end of string)
				std::size_t soh_pos = in.find(soh, eq_pos + 1);
				if (soh_pos == std::string::npos)
					soh_pos = in.size();

				// Extract value (everything from after '=' to SOH)
				std::string value = in.substr(eq_pos + 1, soh_pos - eq_pos - 1);

				// Store first value as magic (should be BeginString)
				if (ret.magic_.empty())
				{
					ret.magic_	   = value;
					ret.magic_len_ = value.size();
				}

				// Store tag-value pair
				ret.message_[tag] = value;

				// Move to position after the SOH
				off = soh_pos + 1;
			}

			return ret;
		}
	};

	using fix_tag_type = std::string;

	using range_data = basic_range_data;
	using visitor	 = basic_visitor;
} // namespace ocl::fix

#endif // ifndef _OCL_FIX_PARSER_HPP