/* 
 * File: opt.hpp
 * Author: Amlal El Mahrouss, 
 * Copyright 2023-2025, Amlal El Mahrouss all rights reserved. 
 */

#ifndef _STDX_OPT_HPP
#define _STDX_OPT_HPP

#include <stdexcept>
#include <utility>

namespace stdx
{
	enum class ret
	{
		okay,
		err
	};

	struct opt final
	{
		explicit opt(const ret& ret)
			: m_ret(ret)
		{
		}

		opt& expect(const char* input)
		{
			if (m_ret == ret::err)
			{
				throw std::runtime_error(input);
			}

			return *this;
		}

	private:
		ret m_ret;
	};

	template <typename Teller, typename... Lst>
	inline stdx::ret eval(Teller tell, Lst&&... arg)
	{
		return tell(std::forward<Lst>(arg)...) ? stdx::ret::okay : stdx::ret::err;
	}

	namespace traits
	{
		struct int_eq_teller
		{
			explicit int_eq_teller()
			{
			}

			bool operator()(int a, int b)
			{
				return (a == b);
			}
		};

		struct int_greater_than_teller
		{
			explicit int_greater_than_teller()
			{
			}

			bool operator()(int a, int b)
			{
				return (a > b);
			}
		};

		struct int_less_than_teller
		{
			explicit int_less_than_teller()
			{
			}

			bool operator()(int a, int b)
			{
				return (a < b);
			}
		};
	} // namespace traits

	template <typename... Lst>
	inline ret eval_less_than(Lst&&... arg)
	{
		static traits::int_less_than_teller eq;
		return eq(std::forward<Lst>(arg)...) ? ret::okay : ret::err;
	}

	template <typename... Lst>
	inline ret eval_eq(Lst&&... arg)
	{
		static traits::int_eq_teller less_than;
		return less_than(std::forward<Lst>(arg)...) ? ret::okay : ret::err;
	}

	template <typename... Lst>
	inline ret eval_greater(Lst&&... arg)
	{
		static traits::int_greater_than_teller greater_than;
		return greater_than(std::forward<Lst>(arg)...) ? ret::okay : ret::err;
	}

} /* namespace stdx */

#endif /* ifndef _STDX_OPT_HPP */
