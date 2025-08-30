/*
* File: core/chunk_string.hpp
 * Purpose: String implementation for the OCL C++ library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss
 */

#ifndef OCL_UTILITY_CHUNK_STRING_HPP
#define OCL_UTILITY_CHUNK_STRING_HPP

#include <lib/core/includes.hpp>

namespace ocl
{
	template <typename char_type, std::size_t max_chunk_size = 8196>
	class basic_chunk_string;

	template <typename char_type, std::size_t max_chunk_size>
	struct basic_chunk_string final
	{
	private:
		char_type  packed_chunks_[max_chunk_size / 4];
		char_type* extended_chunks_ = new char_type[max_chunk_size];

		std::size_t chunk_total_{};

		bool bad_{false};

	public:
    const bool& bad{bad_};

		basic_chunk_string() = default;

		basic_chunk_string(const char_type* in)
		{
			this->operator+=(in);
		}

		basic_chunk_string(const std::basic_string<char_type>& in)
		{
			this->operator+=(in);
		}

		~basic_chunk_string() = default;

		basic_chunk_string& operator=(const basic_chunk_string&) = default;
		basic_chunk_string(const basic_chunk_string&)			 = default;

		basic_chunk_string& operator+=(const std::basic_string<char_type>& in)
		{
			if (in.empty() || bad_)
				return *this;

			if (chunk_total_ > max_chunk_size)
			{
        bad_ = true;
				return *this;
			}

			const static auto size_max_chunk = max_chunk_size / 4;

			if (chunk_total_ < size_max_chunk)
				std::memcpy(packed_chunks_ + chunk_total_, in.data(), in.size());
			else
				std::memcpy(extended_chunks_ + chunk_total_, in.data(), in.size());

			chunk_total_ += in.size();

			return *this;
		}

		const std::basic_string<char_type>& str() const noexcept
		{
			return packed_chunks_;
		}

		void print() noexcept
		{
			ocl::io::print(packed_chunks_);

			if (extended_chunks_)
				ocl::io::print(extended_chunks_);
		}
	};

	template <typename char_type>
	inline void print(basic_chunk_string<char_type>& fmt) noexcept
	{
		fmt.print();
	}
} // namespace ocl
#endif // ifndef OCL_UTILITY_CHUNK_STRING_HPP
