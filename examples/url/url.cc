/*
  fix example
  Written by Amlal El Mahrouss.
  Licensed under the Boost Software License
 */

#include <core/error_handler.hpp>
#include <net/url.hpp>
#include <unistd.h>
#include <io/print.hpp>
#include <sys/socket.h>

/* finally test it */
int main(int argc, char** argv)
{
	ocl::net::url url_type(ocl::net::url::file);
  
  url_type /= "bin";
  url_type /= "ls";

  ocl::io::println(url_type.assemble());

	return EXIT_SUCCESS;
}
