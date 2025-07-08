/*
 * File: fix/parser.hpp
 * Purpose: Financial Information Protocol parser implementation in C++.
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp all rights reserved.
 */

#ifndef _SNU_FIX_PARSER_HPP
#define _SNU_FIX_PARSER_HPP

#include <cstdint>
#include <cstddef>
#include <cassert>
#include <utility>
#include <vector>
#include <string>

namespace snu::fix
{
	struct visitor;
	struct range;
	struct range_data;

	/// @brief Buffer+Length structure
	typedef range* range_ptr_t;

	struct range final
	{
		char*	 ascii_bytes_;
		uint16_t length_;
	};

	/// @brief Convert range to usable string.
	inline std::string to_string(range& range) noexcept
	{
		if (range.length_ < 0)
			return "";

		return std::string(range.ascii_bytes_, range.length_);
	}

	/// @brief a range object containing the FIX packet values.
	class range_data final
	{
	public:
		std::string										 msg_magic_;
		std::size_t										 msg_body_len_;
		std::vector<std::pair<std::string, std::string>> msg_body_;
	};

	/// @brief visitor object which returns a fix::range_data instance.
	class visitor final
	{
	public:
		static constexpr auto soh  = '|';
		static constexpr auto base = 10U;

		explicit visitor() = default;
		~visitor()		  = default;

		visitor& operator=(const visitor&) = default;
		visitor(const visitor&)			 = default;

		range_data visit(const std::string& in)
		{
			range_data ret{};

			static thread_local std::string in_tmp;

			try
			{
				for (auto& ch : in)
				{
					if (ch != soh)
					{
						in_tmp += ch;
						continue;
					}

					auto key = in_tmp.substr(0, in_tmp.find("="));
					auto val = in_tmp.substr(in_tmp.find("=") + 1);

					if (ret.msg_magic_.empty())
					{
						ret.msg_magic_ = val;
					}
					else
					{
						ret.msg_body_.emplace_back(std::make_pair(key, val));
						ret.msg_body_len_ += in_tmp.size();
					}

					in_tmp.clear();
				}
			}
			catch (...)
			{
				in_tmp.clear();
				return {};
			}

			in_tmp.clear();
			return ret;
		}
	};
} // namespace snu::fix

#endif // ifndef _SNU_FIX_PARSER_HPP
