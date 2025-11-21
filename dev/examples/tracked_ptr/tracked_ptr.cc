/*
  tracked_ptr example
  written by Amlal El Mahrouss.
  licensed under the Boost Software License
 */

#include <lib/memory/tracked_ptr.hpp>
#include <lib/io/print.hpp>

static void summon_tracked_ptr()
{
	ocl::memory::tracked_ptr<int> ptr = ocl::memory::make_tracked<int>(42);
	std::cout << ptr.data() << "=" << ptr.manager().allocator().allocated_count_ << std::endl;
}

static void summon_leak_tracked_ptr()
{
	ocl::memory::tracked_ptr<int>* ptr = new ocl::memory::tracked_ptr<int>(42);
	std::cout << ptr->data() << "=" << ptr->manager().allocator().allocated_count_ << std::endl;
}

/* finally test it */
int main(int argc, char** argv)
{
	summon_tracked_ptr();
	summon_tracked_ptr();
	summon_tracked_ptr();
	summon_tracked_ptr();

	ocl::memory::tracked_ptr<int> ptr;

	std::cout << ptr.data() << "=" << ptr.manager().allocator().allocated_count_ << std::endl;

	std::cout << "total=" << ptr.manager().allocator().deallocated_count_ << std::endl;
	std::cout << "leak-detected=" << std::boolalpha << (ptr.manager().allocator().allocated_count_ > ptr.manager().allocator().deallocated_count_) << std::endl;

	summon_leak_tracked_ptr();
	summon_leak_tracked_ptr();
	summon_leak_tracked_ptr();
	summon_leak_tracked_ptr();
	summon_leak_tracked_ptr();
	summon_leak_tracked_ptr();
	summon_leak_tracked_ptr();
	summon_leak_tracked_ptr();

	std::cout << "total=" << ptr.manager().allocator().deallocated_count_ << std::endl;
	std::cout << "leak-detected=" << std::boolalpha << (ptr.manager().allocator().allocated_count_ > ptr.manager().allocator().deallocated_count_) << std::endl;

	ocl::memory::must_pass(ptr);

	return EXIT_SUCCESS;
}
