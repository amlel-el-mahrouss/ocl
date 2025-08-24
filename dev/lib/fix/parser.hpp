/*
 * File: fix/parser.hpp
 * Purpose: Financial Information Exchange parser in C++
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp.
 */

#ifndef _SNU_FIX_PARSER_HPP
#define _SNU_FIX_PARSER_HPP

#include <cstddef>
#include <cassert>
#include <utility>
#include <string>
#include <vector>
#include <cstdint>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

namespace snu::fix
{
	template <typename char_type>
	class basic_visitor;

	template <typename char_type>
	struct basic_range;

	template <typename char_type>
	class basic_range_data;

	/// @brief Buffer+Length structure
	template <typename char_type = char>
	using range_ptr_t = basic_range<char_type>;

	namespace detail
	{
		template <typename char_type = char>
		const char_type* begin_fix();

		template <>
		inline const char* begin_fix<char>()
		{
			return "FIX.";
		}

		template <>
		inline const char16_t* begin_fix<char16_t>()
		{
			return u"FIX.";
		}

		template <>
		inline const char8_t* begin_fix<char8_t>()
		{
			return u8"FIX.";
		}
	} // namespace detail

	template <typename char_type = char>
	struct basic_range final
	{
		char_type* bytes_;
		size_t	   length_;

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
	template <typename char_type = char>
	std::basic_string<char_type> to_string(basic_range<char_type>& basic_range) noexcept
	{
		if (basic_range.length_ < 0)
			return std::basic_string<char_type>{};

		return std::basic_string<char_type>(basic_range.ascii_bytes_, basic_range.length_);
	}

	/// @brief a basic_range object containing the FIX packet values.
	template <typename char_type = char>
	class basic_range_data final
	{
	public:
		std::size_t																		   magic_len_;
		std::basic_string<char_type>													   magic_;
		std::size_t																		   body_len_;
		std::vector<std::pair<std::basic_string<char_type>, std::basic_string<char_type>>> body_;

		static inline const char_type* begin = detail::begin_fix<char_type>();

		explicit basic_range_data() = default;
		~basic_range_data()			= default;

		basic_range_data& operator=(const basic_range_data&) = default;
		basic_range_data(const basic_range_data&)			 = default;

		std::basic_string<char_type> operator[](const std::basic_string<char_type>& key)
		{
			if (key.empty())
			{
				return std::basic_string<char_type>{};
			}

			for (const auto& pair : this->body_)
			{
				if (pair.first == key)
				{
					return pair.second;
				}
			}

			return std::basic_string<char_type>{};
		}

		bool is_valid()
		{
			return magic_.starts_with(basic_range_data<char_type>::begin);
		}

		explicit operator bool()
		{
			return this->is_valid();
		}
	};

	/// @brief basic_visitor object which returns a fix::basic_range_data instance.
	template <typename char_type = char>
	class basic_visitor final
	{
	public:
		static constexpr const char_type soh  = '|';
		static constexpr const char_type eq	  = '=';
		static constexpr uint32_t		 base = 10U;

		explicit basic_visitor() = default;
		~basic_visitor()		 = default;

		basic_visitor& operator=(const basic_visitor&) = default;
		basic_visitor(const basic_visitor&)			   = default;

		basic_range<char_type> operator()(const std::basic_string<char_type>& in)
		{
			return this->visit(in);
		}

		basic_range_data<char_type> visit(const std::basic_string<char_type>& in)
		{
			thread_local basic_range_data<char_type> ret{};

			if (in.empty())
				return ret;

			static thread_local std::basic_string<char_type> in_tmp{};

			in_tmp.reserve(in.size());

			try
			{
				for (auto& ch : in)
				{
					if (ch != basic_visitor::soh)
					{
						in_tmp += ch;
						continue;
					}

					std::basic_string<char_type> key = in_tmp.substr(0, in_tmp.find(basic_visitor::eq));
					std::basic_string<char_type> val = in_tmp.substr(in_tmp.find(basic_visitor::eq) + 1);

					if (ret.magic_.empty())
					{
						ret.magic_	   = val;
						ret.magic_len_ = ret.magic_.size();
					}
					else
					{
						ret.body_.emplace_back(std::make_pair(key, val));
						ret.body_len_ += in_tmp.size();
					}

					in_tmp.clear();
				}
			}
			catch (...)
			{
				in_tmp.clear();
				return ret;
			}

			in_tmp.clear();
			return ret;
		}
	};

	template <typename char_type = char>
	inline void must_pass(basic_range_data<char_type>& basic_range)
	{
		if (!basic_range.is_valid())
		{
			::kill(::getpid(), SIGTRAP);
		}
	}

	using fix_tag_type = std::uint32_t;
} // namespace snu::fix

#endif // ifndef _SNU_FIX_PARSER_HPP
