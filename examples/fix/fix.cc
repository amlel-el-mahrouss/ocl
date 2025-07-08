/* 
  string checksum example
  written by Amlal El Mahrouss.
  licensed under the MIT license
 */

#include <lib/fix/parser.hpp>
#include <iostream>

/* finally test it */
int main(int argc, char** argv)
{
	snu::fix::visitor	 visitor;
	snu::fix::range_data fix = visitor.visit("8=FIX.4.2|9=65|35=A|49=SERVER|56=CLIENT|34=177|52=20090107-18:15:16|98=0|108=30|10=062|");

	std::cout << "magic: " << fix.msg_magic_ << std::endl;

	for (auto fields : fix.msg_body_)
	{
		std::cout << "key: " << fields.first;
		std::cout << ", value: " << fields.second << std::endl;
	}

	return 0;
}
