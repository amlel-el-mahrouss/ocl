/*
 * File: cgi_writer.hpp
 * Author: Amlal El Mahrouss,
 * Copyright 2023-2025, Amlal El Mahrouss.
 */

#ifndef _OCL_CGI_WRITER_HPP
#define _OCL_CGI_WRITER_HPP

#include <lib/io/print.hpp>
#include <lib/utility/chunk_string.hpp>
#include <sstream>
#include <format>

namespace ocl
{
	namespace cgi
	{
		/// @brief CGI Writer class, writes to stdout; as CGI expects.
		template <typename char_type = char>
		class basic_writer
		{
		private:
			basic_writer& eval_(const ocl::basic_chunk_string<char_type>& mime, const ocl::basic_chunk_string<char_type>& ss) noexcept
			{
				std::basic_stringstream<char_type> ss_out;

				ss_out << std::format("Content-Type: {}\r\n", mime.str());
				ss_out << std::format("Server: {}\r\n", "OCL-CGI/1.0");
				ss_out << std::format("Content-Length: {}\r\n\r\n", ss.str().size());
				ss_out << ss.str();

				ocl::io::print(ss_out.str());

				return *this;
			}

		public:
			explicit basic_writer() = default;
			~basic_writer()			= default;

			basic_writer& operator=(const basic_writer&) = default;
			basic_writer(const basic_writer&)			 = default;

		public:
			friend void operator<<(basic_writer& self, const ocl::basic_chunk_string<char_type>& ss_in)
			{
				self = self.eval_("text/plain", ss_in);
			}

			basic_writer& binary(const ocl::basic_chunk_string<char_type>& ss_in)
			{
				return this->eval_("application/octet-stream", ss_in);
			}

			basic_writer& html(const ocl::basic_chunk_string<char_type>& ss_in)
			{
				return this->eval_("text/html", ss_in);
			}

			basic_writer& xml(const ocl::basic_chunk_string<char_type>& ss_in)
			{
				return this->eval_("application/xml", ss_in);
			}

			basic_writer& json(const ocl::basic_chunk_string<char_type>& ss_in)
			{
				return this->eval_("application/json", ss_in);
			}

			basic_writer& js(const ocl::basic_chunk_string<char_type>& ss_in)
			{
				return this->eval_("text/javascript", ss_in);
			}
		};
	} // namespace cgi
} // namespace ocl

#endif // ifndef _OCL_CGI_WRITER_HPP
