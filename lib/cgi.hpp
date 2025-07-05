/*
 * File: cgi.hpp
 * Author: Amlal El Mahrouss,
 * Copyright 2023-2025, Amlal El Mahrouss all rights reserved.
 */

#ifndef _SNU_CGI_HPP
#define _SNU_CGI_HPP

#include <cstdio>
#include <string>
#include <sstream>

namespace snu
{
	namespace web
	{
		/// @brief CGI Writer class, writes to stdout; as CGI expects.
		class cgi_writer final
		{
			cgi_writer& eval_(const std::string& mime, const std::stringstream& ss) noexcept
			{
				std::printf("Content-Type: %s\r\n", mime.c_str());
				std::printf("Server: %s\r\n", "snu-cpp-library");
				std::printf("Content-Length: %ld\r\n\r\n", ss.str().size());
				std::printf("%s", ss.str().c_str());

				return *this;
			}

		public:
			explicit cgi_writer() = default;
			~cgi_writer()		  = default;

			cgi_writer& operator=(const cgi_writer&) = default;
			cgi_writer(const cgi_writer&)			 = default;

		public:
			cgi_writer& eval_html(const std::stringstream& ss_html)
			{
				return this->eval_("text/html", ss_html);
			}

			cgi_writer& eval_xml(const std::stringstream& ss_html)
			{
				return this->eval_("application/xml", ss_html);
			}

			cgi_writer& eval_json(const std::stringstream& ss_html)
			{
				return this->eval_("application/json", ss_html);
			}

			cgi_writer& eval_js(const std::stringstream& ss_html)
			{
				return this->eval_("text/javascript", ss_html);
			}
		};
	} // namespace web
} // namespace snu

#endif // ifndef _SNU_CGI_HPP