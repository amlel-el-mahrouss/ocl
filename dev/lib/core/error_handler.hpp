/*
* File: core/basic_error_handler.hpp
* Purpose: Error handler container.
* Author: Amlal El Mahrouss (amlal@nekernel.org)
* Copyright 2025, Amlal El Mahrouss.
*/

#ifndef _SCL_ERROR_HANDLER_HPP
#define _SCL_ERROR_HANDLER_HPP

#include <lib/core/includes.hpp>
#include <lib/io/print.hpp>

namespace scl
{
	struct basic_error_handler;

	struct basic_error_handler
	{
		explicit basic_error_handler() = default;
		virtual ~basic_error_handler() = default;

		basic_error_handler& operator=(const basic_error_handler&) = delete;
		basic_error_handler(const basic_error_handler&)			   = delete;

		virtual void operator()(const std::basic_string<char>& msg)
		{
			scl::io::print(msg);
		}
	};

	using standard_error_handler = basic_error_handler;
	using error_handler_type	 = basic_error_handler;
} // namespace scl

#endif // ifndef _SCL_ERROR_HANDLER_HPP
