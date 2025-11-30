/*
 * File: core/handler.hpp
 * Purpose: Handler container.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, Licensed under the Boost Software License.
 */

#ifndef _OCL_ERROR_HANDLER_HPP
#define _OCL_ERROR_HANDLER_HPP

#include <core/config.hpp>
#include <io/print.hpp>
#include <exception>

namespace ocl
{
	struct handler;

	struct handler
	{
	private:
		template <typename T>
		void handle_impl(T element) {}

	public:
		using error_type = std::exception;

		explicit handler() = default;
		virtual ~handler() = default;

		handler& operator=(const handler&) = default;
		handler(const handler&)			   = default;

		template <typename T>
		void operator()(T element)
		{
			this->handle_impl<T>(element);
		}
	};
} // namespace ocl

#endif // ifndef _OCL_ERROR_HANDLER_HPP
