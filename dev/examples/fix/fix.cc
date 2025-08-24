/*
  fix example
  written by Amlal El Mahrouss.
  licensed under the MIT license
 */

#include <lib/net/modem.hpp>
#include <lib/fix/parser.hpp>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

/* finally test it */
int main(int argc, char** argv)
{
	constexpr auto default_fix = "8=FIX.4.2|9=65|35=A|49=SERVER|56=CLIENT|34=177|52=20090107-18:15:16|98=0|108=30|10=062|";

	snu::fix::basic_visitor<char>	   basic_visitor;
	snu::fix::basic_range_data<char> fix = basic_visitor.visit(default_fix);

	std::cout << "magic=" << fix.magic_ << std::endl;
	std::cout << "magic_len=" << fix.magic_len_ << std::endl;
	std::cout << "is_valid=" << std::boolalpha << fix.is_valid() << std::endl;

	snu::fix::must_pass(fix);

	for (auto fields : fix.body_)
	{
		std::cout << "key=" << fields.first;
		std::cout << ":value=" << fields.second << std::endl;
	}

	return 0;
}
