/*
 * File: core/chunk_string.hpp
 * Purpose: String implementation for the OCL C++ library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss
 */

#ifndef OCL_UTILITY_CHUNK_STRING_HPP
#define OCL_UTILITY_CHUNK_STRING_HPP

#include <core/config.hpp>
#include <io/print.hpp>
#include <cstring>

namespace ocl
{
	template <typename char_type, std::size_t max_chunk_size = 8196>
	class basic_chunk_string;

	template <typename char_type, std::size_t max_chunk_size>
	class basic_chunk_string final
	{
	public:
		using condition_type = bool;

	private:
		char_type	packed_chunks_[max_chunk_size] = {0};
		std::size_t chunk_total_{};

		condition_type bad_{false};

	public:
		const condition_type& bad{bad_};

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

		basic_chunk_string& operator=(const basic_chunk_string&) = delete;
		basic_chunk_string(const basic_chunk_string&)			 = delete;

	public:
		/// @brief Append a std::basic_string to the chunk string.
		basic_chunk_string& operator+=(const char_type* in)
		{
			if (in == nullptr || bad_)
				return *this;

			this->operator+=(std::basic_string<char_type>(in));

			return *this;
		}

		basic_chunk_string& operator+=(const std::basic_string<char_type>& in)
		{
			if (in.empty() || bad_)
				return *this;

			if (in.size() > max_chunk_size)
			{
				bad_ = true;
				return *this;
			}

			if (chunk_total_ > max_chunk_size)
			{
				bad_ = true;
				return *this;
			}

			const auto&		  sz			 = in.size();
			const static auto size_max_chunk = max_chunk_size;
			const auto&		  ptr			 = in.data();

			if (chunk_total_ < size_max_chunk)
			{
				std::memcpy(packed_chunks_ + chunk_total_, ptr, sz);
				chunk_total_ += sz;
			}

			return *this;
		}

		/// @brief Convert to basic_string or return from cache.
		std::basic_string<char_type> str() const noexcept
		{
			static std::basic_string<char_type> ret;
			const auto&							sz = ret.size();

			if (chunk_total_ > sz)
				ret.clear();
			else
				return ret;

			ret = packed_chunks_;

			return ret;
		}

		void print() noexcept
		{
			ocl::io::print(packed_chunks_);
		}
	};

	template <typename char_type>
	inline void print(basic_chunk_string<char_type>& fmt) noexcept
	{
		fmt.print();
	}
} // namespace ocl
#endif // ifndef OCL_UTILITY_CHUNK_STRING_HPP
