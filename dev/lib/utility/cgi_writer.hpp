/*
 * File: cgi_writer.hpp
 * Author: Amlal El Mahrouss,
 * Copyright 2023-2025, Amlal El Mahrouss.
 */

#ifndef _SNU_CGI_WRITER_HPP
#define _SNU_CGI_WRITER_HPP

#include <cstdio>
#include <string>
#include <sstream>

namespace snu
{
	namespace cgi
	{
		/// @brief CGI Writer class, writes to stdout; as CGI expects.
		template <typename char_type = char>
		class basic_writer
		{
		private:
			basic_writer& eval_(const std::basic_string<char>& mime, const std::basic_stringstream<char_type>& ss) noexcept
			{
				std::printf("Content-Type: %s\r\n", mime.c_str());
				std::printf("Server: %s\r\n", "socl-cgi-system");
				std::printf("Content-Length: %ld\r\n\r\n", ss.str().size());

				auto ss_cc = ss.str();

				for (auto& ch : ss_cc)
				{
					std::printf("%c", ch);
				}

				return *this;
			}

		public:
			explicit basic_writer() = default;
			~basic_writer()			= default;

			basic_writer& operator=(const basic_writer&) = default;
			basic_writer(const basic_writer&)			 = default;

		public:
			basic_writer& binary(const std::basic_stringstream<char_type>& ss_in)
			{
				return this->eval_("application/octet-stream", ss_in);
			}

			basic_writer& html(const std::basic_stringstream<char_type>& ss_in)
			{
				return this->eval_("text/html", ss_in);
			}

			basic_writer& xml(const std::basic_stringstream<char_type>& ss_in)
			{
				return this->eval_("application/xml", ss_in);
			}

			basic_writer& json(const std::basic_stringstream<char_type>& ss_in)
			{
				return this->eval_("application/json", ss_in);
			}

			basic_writer& js(const std::basic_stringstream<char_type>& ss_in)
			{
				return this->eval_("text/javascript", ss_in);
			}
		};
	} // namespace cgi
} // namespace snu

#endif // ifndef _SNU_CGI_WRITER_HPP
