/*
  fix example
  written by Amlal El Mahrouss.
  licensed under the Boost Software License
 */

#include <core/error_handler.hpp>
#include <net/modem.hpp>
#include <fix/fix.hpp>
#include <iostream>
#include <unistd.h>
#include <io/print.hpp>
#include <sys/socket.h>

/* finally test it */
int main(int argc, char** argv)
{
	constexpr auto default_fix = "8=FIX.4.2\x01 9=65 \x01 35=A \x01 49=SERVER \x01 56=CLIENT \x01 34=177 \x01 52=20090107-18:15:16 \x01 98=0 \x01 108=30 \x01 10=062 \x01 ";

	ocl::fix::basic_visitor<char>	   basic_visitor;
	ocl::fix::basic_range_data<char> fix = basic_visitor.visit(default_fix);

	std::cout << "magic=" << fix.magic_ << std::endl;
	std::cout << "magic_len=" << fix.magic_len_ << std::endl;
	std::cout << "is_valid=" << std::boolalpha << fix.is_valid() << std::endl;

	ocl::basic_error_handler handler;
	ocl::fix::must_pass<char, ocl::basic_error_handler>(fix, handler);

	for (auto fields : fix.body_)
	{
		ocl::io::print("key=", fields.first); 
		ocl::io::print(", value=", fields.second);
	}

	return 0;
}
