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
	struct basic_hash final
	{
		using result_type = typename T::result_type;
		using type		  = T;

		// AMLALE: If it throws, we can't compute the hash correctly.
		static constexpr result_type hash() noexcept
		{
			return T{}.hash();
		}
	};

	template <typename T, typename U>
	struct is_same
	{
		using left_type	 = T;
		using right_type = T;

		static constexpr bool value = false;
	};

	template <typename T>
	struct is_same<T, T>
	{
		static constexpr bool value = true;
	};

	template <typename T, typename U>
	struct is_not_same
	{
		using left_type	 = T;
		using right_type = T;

		static constexpr bool value = true;
	};

	template <typename T>
	struct is_not_same<T, T>
	{
		static constexpr bool value = false;
	};

	template <typename T>
	struct equiv_is_int8 final
	{
		using result_type = bool;

		static constexpr auto value = sizeof(T) == 1;
	};

	template <typename T>
	struct equiv_not_int8 final
	{
		using result_type = bool;

		static constexpr auto value = sizeof(T) > 1;
	};

	template <typename T>
	struct equiv_is_real final
	{
		using result_type = bool;

		static constexpr auto value = sizeof(T) >= 4;
	};

	template <typename L, typename R>
	struct equiv_is final
	{
		using result_type = bool;
		using left_type	  = L;
		using right_type  = R;

		static constexpr auto value = false;
	};

	template <typename L>
	struct equiv_is<L, L> final
	{
		using result_type = bool;
		using left_type	  = L;
		using right_type  = L;

		static constexpr auto value = true;
	};
} // namespace ocl

#endif