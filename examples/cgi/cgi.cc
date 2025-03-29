/* 
 cgi example
  written by Amlal El Mahrouss.
  licensed under GPL-2 license
 */

#include <fstream>
#include <sstream>
#include <stdx/cgi.hpp>
#include <string>
#include <filesystem>

/* finally test it */
int main(int argc, char** argv)
{
	// ... let's assume we serve data.

	stdx::web::cgi_writer writer;
	std::stringstream	  ss_file;

	std::ifstream fp("index.html");

	if (fp.good())
		ss_file << fp.rdbuf();
	else
		ss_file << "<!DOCTYPE html>\n<html></html>";

	fp.close();

	writer.eval_html(ss_file);

	return 0;
}
