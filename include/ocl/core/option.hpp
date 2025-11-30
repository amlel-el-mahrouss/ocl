/*
 * File: option.hpp
 * Author: Amlal El Mahrouss,
 * Copyright 2023-2025, Amlal El Mahrouss, Licensed under the Boost Software License
 */

#ifndef _OCL_OPT_HPP
#define _OCL_OPT_HPP

#include <core/config.hpp>
#include <utility>

namespace ocl
{
	enum class return_type
	{
		invalid = 0,
		okay	= 100,
		err,
		count = err - okay + 1,
	};

	template <typename char_type = char>
	struct option final
	{
		explicit option(const return_type& return_type)
			: ret_(return_type)
		{
		}

		~option() = default;

		option& operator=(const option&) = default;
		option(const option&)			   = default;

		option& expect(const char_type* input)
		{
			if (ret_ == return_type::err)
			{
				throw std::runtime_error(input ? input : "option::error");
			}

			return *this;
		}

		template <typename ErrorHandler>
		option& expect_or_handle(const char_type* input)
		{
			if (ret_ == return_type::err)
			{
				ErrorHandler err_handler;
				err_handler(input ? input : "option::error");
			}

			return *this;
		}

	private:
		return_type ret_{return_type::invalid};
	};

	template <typename Teller, typename... Lst>
	inline return_type eval(Teller tell, Lst&&... arg)
	{
		return tell(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	namespace traits
	{
		struct int_eq_teller
		{
			bool operator()(int a, int b)
			{
				return (a == b);
			}
		};

		struct int_greater_than_teller
		{
			bool operator()(int a, int b)
			{
				return (a > b);
			}
		};

		struct int_less_than_teller
		{
			bool operator()(int a, int b)
			{
				return (a < b);
			}
		};
	} // namespace traits

	template <typename... Lst>
	inline return_type eval_less_than(Lst&&... arg)
	{
		static traits::int_less_than_teller eq;
		return eq(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	template <typename... Lst>
	inline return_type eval_eq(Lst&&... arg)
	{
		static traits::int_eq_teller less_than;
		return less_than(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	template <typename... Lst>
	inline return_type eval_greater_than(Lst&&... arg)
	{
		static traits::int_greater_than_teller greater_than;
		return greater_than(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	inline return_type eval_true() noexcept
	{
		return return_type::okay;
	}

	inline return_type eval_false() noexcept
	{
		return return_type::err;
	}
} // namespace ocl

#endif /* ifndef _OCL_OPT_HPP */