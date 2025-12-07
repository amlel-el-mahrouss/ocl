/*
 * File: is_same.hpp
 * Purpose: Equivalence header.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef __OCL_CORE_IS_SAME
#define __OCL_CORE_IS_SAME

#include <ocl/detail/config.hpp>

/// @brief OCL equivalence namespace.
namespace ocl
{
	template <typename T>
	struct basic_hash
	{
		using result_type = typename T::result_type;
		using type		  = T;

		/// @brief hash from T's result_type.
		static result_type hash()
		{
			return T{}.hash();
		}
	};

	template <typename T, typename U>
	struct is_same
	{
		static constexpr bool value = false;

		/// @brief check if hash matches what we expect.
		constexpr bool operator()() noexcept
		{
			return T::hash() == U::hash();
		}
	};

	template <typename T>
	struct is_same<T, T>
	{
		static constexpr bool value = true;
	};

	template <typename T, typename U>
	struct is_not_same
	{
		static constexpr bool value = true;

		constexpr bool operator()() noexcept
		{
			return T::hash() != U::hash();
		}
	};

	template <typename T>
	struct is_not_same<T, T>
	{
		static constexpr bool value = false;
	};

	template <typename T>
	struct equiv_is_int8
	{
	private:
		T left_ = 127, right_ = 127;

	public:
		using result_type = bool;

		constexpr result_type hash()
		{
			return (left_ + right_) < 1;
		}
	};

	template <typename T>
	struct equiv_not_int8
	{
	private:
		// these shall overflow if not int8.
		T left_ = 127, right_ = 127;

	public:
		using result_type = bool;

		constexpr result_type hash()
		{
			return (left_ + right_) > 0;
		}
	};

	template <typename T>
	struct equiv_is_real
	{
	private:
		T left_ = 5, right_ = 3;

	public:
		using result_type = bool;

		constexpr result_type hash()
		{
			return (left_ / right_) == 1;
		}
	};

	template <typename T>
	struct equiv_is
	{
	private:
		T left_{}, right_{};

	public:
		using result_type = bool;

		constexpr result_type hash()
		{
			return (left_ / right_);
		}
	};
} // namespace ocl

#endif