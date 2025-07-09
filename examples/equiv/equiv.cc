/* 
  string checksum example
  written by Amlal El Mahrouss.
  licensed under the MIT license
 */

#include <lib/equiv.hpp>
#include <iostream>

/* finally test it */
int main(int argc, char** argv)
{
	std::cout << std::boolalpha;
	std::cout << snu::equiv::is_same<bool, int>::value << std::endl;
	std::cout << snu::equiv::is_same<bool, bool>::value << std::endl;
	std::cout << snu::equiv::is_same<int, int>::value << std::endl;

	return 0;
}
