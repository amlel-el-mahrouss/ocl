/*
* File: core/basic_error_handler.hpp
* Purpose: Error handler container.
* Author: Amlal El Mahrouss (amlal@nekernel.org)
* Copyright 2025, Amlal El Mahrouss, Licensed under the Boost Software License.
*/

#ifndef _OCL_ERROR_HANDLER_HPP
#define _OCL_ERROR_HANDLER_HPP

#include <core/includes.hpp>
#include <io/print.hpp>

namespace ocl
{
	struct basic_error_handler;

	struct basic_error_handler
	{
		explicit basic_error_handler() = default;
		virtual ~basic_error_handler() = default;

		basic_error_handler& operator=(const basic_error_handler&) = delete;
		basic_error_handler(const basic_error_handler&)			   = delete;

		template <bool throw_too = false>
		void error(const std::basic_string<char>& msg)
		{
			this->operator()(msg);

			if constexpr (throw_too)
			{
				throw std::runtime_error(msg);
			}
		}

		void operator()(const std::basic_string<char>& msg)
		{
			ocl::io::print(msg);
		}
	};

	using standard_error_handler = basic_error_handler;
	using error_handler_type	 = basic_error_handler;
} // namespace ocl

#endif // ifndef _OCL_ERROR_HANDLER_HPP
