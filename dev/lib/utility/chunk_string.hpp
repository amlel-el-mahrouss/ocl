/*
* File: core/chunk_string.hpp
 * Purpose: String implementation for the SOCL C++ library.
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss and SNU Systems Corp.
 */

#ifndef SOCL_UTILITY_CHUNK_STRING_HPP
#define SOCL_UTILITY_CHUNK_STRING_HPP

#include <lib/core/includes.hpp>
#include <boost/container/flat_set.hpp>

namespace snu
{
	template <typename char_type>
	class basic_chunk_string;

	template <typename char_type>
	struct basic_chunk_string final
	{
	private:
		std::unique_ptr<basic_chunk_string<char_type>> next_chunk_string_{};
		basic_chunk_string<char_type>*				   prev_chunk_string_{nullptr};

		std::basic_string<char_type> packed_chunks_{};
		int64_t						 chunk_total{};

		constexpr const static auto max_chunk_size = 4096;

	public:
		explicit basic_chunk_string() = default;
		virtual ~basic_chunk_string() = default;

		basic_chunk_string& operator=(const basic_chunk_string&) = default;
		basic_chunk_string(const basic_chunk_string&)			 = default;

		basic_chunk_string& operator+=(const std::basic_string<char_type>& in)
		{
			if (in.empty())
				return *this;

			if (chunk_total > max_chunk_size)
			{
				next_chunk_string_ = std::make_unique<basic_chunk_string<char_type>>();
				*next_chunk_string_ += in;

				next_chunk_string_->prev_chunk_string_ = this;

				return *next_chunk_string_;
			}

			packed_chunks_ += in;
			chunk_total += in.size();

			return *this;
		}

		const std::basic_string<char_type>& str() noexcept
		{
			return packed_chunks_;
		}

		inline void print() noexcept
		{
			snu::io::print(packed_chunks_);

			if (next_chunk_string_)
				this->next_chunk_string_->print();
		}
	};

	template <typename char_type>
	inline void print(basic_chunk_string<char_type>& fmt) noexcept
	{
		std::cout << fmt.print();
	}
} // namespace snu
#endif // ifndef SOCL_UTILITY_CHUNK_STRING_HPP