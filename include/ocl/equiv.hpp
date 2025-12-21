/*
 * File: equiv.hpp
 * Purpose: Equivalence header.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef __OCL_CORE_EQUIV
#define __OCL_CORE_EQUIV

#include <ocl/detail/config.hpp>

/// @brief OCL equivalence namespace.
namespace ocl
{
	template <typename T>
	struct is_real final
	{
		using type					= T;
		static constexpr auto value = false;
	};

	template <typename L, typename R>
	struct equiv_to final
	{
		using left_type	 = L;
		using right_type = R;

		static constexpr auto value = false;
	};

	template <typename L>
	struct equiv_to<L, L> final
	{
		static constexpr auto value = true;
	};

	template <>
	struct is_real<double> final
	{
		static constexpr auto value = true;
	};

	template <>
	struct is_real<float> final
	{
		static constexpr auto value = true;
	};
} // namespace ocl

#endif
