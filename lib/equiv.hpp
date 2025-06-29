/*
 * File: equiv.hpp
 * Purpose: equivalence runtime c++ header.
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss all rights reserved.
 */

#pragma once

namespace snu
{
	template <typename T>
	struct basic_hash_trait
	{
		/// @brief hash from T's result.
		static typename T::result hash()
		{
			static T val;
			return val.hash();
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
		T left_ = 255, right_ = 255;

	public:
		using result = T;

		constexpr result hash()
		{
			return (left_ + right_) < 1;
		}
	};

	template <typename T>
	struct equiv_not_int8
	{
	private:
		T left_ = 255, right_ = 255;

	public:
		using result = T;

		constexpr result hash()
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
		using result = T;

		constexpr result hash()
		{
			return left_ / right_;
		}
	};
} // namespace snu