/* 
  string checksum example
  written by Amlal El Mahrouss.
  licensed under GPL-2 license
 */

#include <lib/equiv.hpp>
#include <iostream>

/* finally test it */
int main(int argc, char** argv)
{
	std::cout << std::boolalpha;
	std::cout << snu::is_same<bool, int>::value << std::endl;
	std::cout << snu::is_same<bool, bool>::value << std::endl;
	std::cout << snu::is_same<int, int>::value << std::endl;

	return 0;
}
