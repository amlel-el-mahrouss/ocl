/*
 * File: option.hpp
 * Author: Amlal El Mahrouss,
 * Copyright 2023-2025, Amlal El Mahrouss, Licensed under the Boost Software License
 */

#ifndef __OCL_CORE_OPTION
#define __OCL_CORE_OPTION

#include <ocl/detail/config.hpp>
#include <utility>

namespace ocl
{
	enum struct return_type : int
	{
		invalid = 0,
		okay	= 100,
		err,
		count = err - okay + 1,
	};

	namespace detail
	{
		using option_error = std::runtime_error;

		void throw_option_invalid_type_error()
		{
			throw option_error("option has invalid type.");
		}
	} // namespace detail

	class option final
	{
	public:
		option() = delete;
		explicit option(const return_type& return_type)
			: ret_(return_type)
		{
			if (ret_ == return_type::invalid)
				detail::throw_option_invalid_type_error();
		}

		~option() = default;

		option& operator=(const option&) = delete;
		option(const option&)			 = delete;

		option& expect(const char* input)
		{
			assert(ret_ != return_type::invalid);

			if (ret_ == return_type::err)
			{
				throw detail::option_error(input ? input : "option::error");
			}

			return *this;
		}

		template <typename Handleable>
		option& expect_or_handle(const char* input)
		{
			assert(ret_ != return_type::invalid);

			if (ret_ == return_type::err)
			{
				// AMLALE: Shall it be a functor or container here?
				Handleable(input ? input : "option::error");
			}

			return *this;
		}

	private:
		return_type ret_{return_type::invalid};
	};

	namespace detail
	{
		// AMLALE: The operator() are marked as `noexcept` as failing conditions within an evaluation (say a overloads operator==) proves that the
		// predictate is wrong. Thus program state is undefined.

		struct teller
		{
			teller()		  = default;
			virtual ~teller() = default;

			template <class ObjFirst, class ObjLast>
			bool operator()(ObjFirst a, ObjLast b) noexcept
			{
				return false;
			}
		};

		struct eq_teller final : teller
		{
			template <class ObjFirst, class ObjLast>
			bool operator()(ObjFirst a, ObjLast b) noexcept
			{
				return (a == b);
			}
		};

		struct greater_than_teller final : teller
		{
			template <class ObjFirst, class ObjLast>
			bool operator()(ObjFirst a, ObjLast b) noexcept
			{
				return (a > b);
			}
		};

		struct less_than_teller final : teller
		{
			template <class ObjFirst, class ObjLast>
			bool operator()(ObjFirst a, ObjLast b) noexcept
			{
				return (a < b);
			}
		};
	} // namespace detail

	template <typename Teller, typename... Lst>
	inline return_type eval(const Teller& tell, Lst&&... arg)
	{
		static_assert(std::is_base_of_v<detail::teller, Teller>, "Teller is not evalueable.");
		return tell(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	template <typename... Lst>
	inline return_type eval_less_than(Lst&&... arg)
	{
		return detail::less_than_teller{}(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	template <typename... Lst>
	inline return_type eval_eq(Lst&&... arg)
	{
		return detail::eq_teller{}(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	template <typename... Lst>
	inline return_type eval_greater_than(Lst&&... arg)
	{
		return detail::greater_than_teller{}(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	inline return_type eval_true() noexcept
	{
		return return_type::okay;
	}

	inline return_type eval_false() noexcept
	{
		return return_type::err;
	}

	inline return_type eval_invalid() noexcept
	{
		return return_type::invalid;
	}
} // namespace ocl

#endif /* ifndef __OCL_CORE_OPTION */
