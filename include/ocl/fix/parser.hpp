/*
 * File: fix/parser.hpp
 * Purpose: Financial Information Exchange parser in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef _OCL_FIX_PARSER_HPP
#define _OCL_FIX_PARSER_HPP

#include <algorithm>
#include <core/config.hpp>
#include <string>
#include <io/print.hpp>

namespace ocl::fix
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
		const char_type* begin_fix() noexcept;

		template <>
		inline const char* begin_fix<char>() noexcept
		{
			return "FIX.4.2";
		}

		template <>
		inline const char16_t* begin_fix<char16_t>() noexcept
		{
			return u"FIX.4.2";
		}

		template <>
		inline const char8_t* begin_fix<char8_t>() noexcept
		{
			return u8"FIX.4.2";
		}
	} // namespace detail

	template <typename char_type = char>
	struct basic_range final
	{
		char_type* bytes_{nullptr};
		size_t	   length_{};

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
	inline std::basic_string<char_type> to_string(basic_range<char_type>& basic_range) noexcept
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
		std::size_t																		   magic_len_{};
		std::basic_string<char_type>													   magic_{};
		std::size_t																		   body_len_{};
		std::vector<std::pair<std::basic_string<char_type>, std::basic_string<char_type>>> body_{};

		static inline const char_type* begin = detail::begin_fix<char_type>();

		explicit basic_range_data() = default;
		~basic_range_data()			= default;

		basic_range_data& operator=(const basic_range_data&) = default;
		basic_range_data(const basic_range_data&)			 = default;

		std::basic_string<char_type> operator[](const std::basic_string<char_type>& key)
		{
			if (key.empty())
				return std::basic_string<char_type>{};

			auto it = std::find_if(this->body_.begin(), this->body_.end(), [&key](const std::pair<std::basic_string<char_type>, std::basic_string<char_type>>& in) {
				return in.first == key;
			});

			if (it != this->body_.cend())
				return it->second;

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
		/// AMLALE: Yeah...
		static constexpr const int		 soh  = '\x01';
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

		/// @brief Visit a FIX message and parse it into a basic_range_data object.
		/// @param in The input FIX message as a string.
		/// @warning This function may throw exceptions.
		basic_range_data<char_type> visit(std::basic_string<char_type> in)
		{
			basic_range_data<char_type> ret{};

			if (in.empty())
				return ret;

			std::basic_string<char_type> key;

			std::size_t off = 0UL;

			while (true)
			{
				if (in.size() < off)
					break;

				if (in[off] != basic_visitor::eq)
				{
					if (in[off] == basic_visitor::soh)
					{
						++off;
						continue;
					}

					key += in[off];
					++off;
					continue;
				}

				if (in.size() < (off + 1))
					break;

				std::basic_string<char_type> val = in.substr(off + 1);

				if (val.find(basic_visitor::soh) != std::basic_string<char_type>::npos)
				{
					val.erase(val.find(basic_visitor::soh));
				}

				if (ret.magic_.empty())
				{
					ret.magic_	   = val;
					ret.magic_len_ = ret.magic_.size();
				}

				ret.body_.emplace_back(std::make_pair(key, val));

				off += val.size() + 1;

				key.clear();
			}

			ret.body_len_ = ret.body_.size();

			return ret;
		}
	};

	template <typename char_type = char, typename error_handler>
	inline void must_pass(basic_range_data<char_type>& basic_range, error_handler& handler)
	{
		if (!basic_range.is_valid())
		{
			handler.template error<true>("Invalid FIX Message.");
		}
	}

	using fix_tag_type = std::uint32_t;

	using range_data = basic_range_data<char>;
	using visitor	 = basic_visitor<char>;
} // namespace ocl::fix

#endif // ifndef _OCL_FIX_PARSER_HPP