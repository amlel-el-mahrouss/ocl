/*
* File: fix/parser.hpp
* Purpose: Error handler container.
* Author: Amlal El Mahrouss (amlal@nekernel.org)
* Copyright 2025, Amlal El Mahrouss.
*/

#ifndef _OCL_ERROR_HANDLER_HPP
#define _OCL_ERROR_HANDLER_HPP

#include <lib/core/includes.hpp>
#include <stdexcept>

namespace ocl
{
	struct basic_error_handler;

	struct basic_error_handler
	{
		explicit basic_error_handler() = default;
		virtual ~basic_error_handler() = default;

		basic_error_handler& operator=(const basic_error_handler&) = delete;
		basic_error_handler(const basic_error_handler&)			   = delete;

		void operator()(const std::basic_string<char>& msg)
		{
			throw std::runtime_error(msg);
		}
	};

	using standard_error_handler = basic_error_handler;
} // namespace ocl

#endif // ifndef _OCL_ERROR_HANDLER_HPP
