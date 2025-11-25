/*
  fix example
  written by Amlal El Mahrouss.
  licensed under the Boost Software License
 */

#include <core/error_handler.hpp>
#include <net/modem.hpp>
#include <fix/parser.hpp>
#include <iostream>
#include <unistd.h>
#include <io/print.hpp>
#include <sys/socket.h>

/* finally test it */
int main(int argc, char** argv)
{
	constexpr const char default_fix[] = {
		'8', '=', 'F', 'I', 'X', '.', '4', '.', '2', 0x01,
		'9', '=', '6', '3', 0x01, // BodyLength = 63
		'3', '5', '=', 'A', 0x01,
		'4', '9', '=', 'S', 'E', 'R', 'V', 'E', 'R', 0x01,
		'5', '6', '=', 'C', 'L', 'I', 'E', 'N', 'T', 0x01,
		'3', '4', '=', '1', '7', '7', 0x01,
		'5', '2', '=', '2', '0', '0', '9', '0', '1', '0', '7', '-', '1', '8', ':', '1', '5', ':', '1', '6', 0x01,
		'9', '8', '=', '0', 0x01,
		'1', '0', '8', '=', '3', '0', 0x01,
		'1', '0', '=', '1', '4', '3', 0x01, 0x00 // CheckSum = 143
	};

	ocl::fix::basic_visitor<char>	 basic_visitor;
	ocl::fix::basic_range_data<char> fix = basic_visitor.visit(default_fix);

	std::cout << "magic=" << fix.magic_ << std::endl;
	std::cout << "magic_len=" << fix.magic_len_ << std::endl;
	std::cout << "is_valid=" << std::boolalpha << fix.is_valid() << std::endl;

	ocl::basic_error_handler handler;
	ocl::fix::must_pass<char, ocl::basic_error_handler>(fix, handler);

	ocl::io::print(":key=9\n");
	ocl::io::print(":value=", fix["35"], "\n");

	return 0;
}
