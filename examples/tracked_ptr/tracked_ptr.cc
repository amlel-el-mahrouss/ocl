/* 
  tracked_ptr example
  written by Amlal El Mahrouss.
  licensed under the MIT license
 */

#include <lib/memory/tracked_ptr.hpp>
#include <iostream>

void foo()
{
	snu::memory::tracked_ptr<int> ptr;
	std::cout << ptr.data() << "=" << ptr.manager().allocator().allocated_count_ << std::endl;
}

/* finally test it */
int main(int argc, char** argv)
{
	foo();
	foo();
	foo();
	foo();

	snu::memory::tracked_ptr<int> ptr;

	std::cout << ptr.data() << "=" << ptr.manager().allocator().allocated_count_ << std::endl;
	std::cout << "total=" << ptr.manager().allocator().deallocated_count_ << std::endl;

	return 0;
}
