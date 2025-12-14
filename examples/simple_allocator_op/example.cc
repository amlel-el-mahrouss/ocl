#include <ocl/print.hpp>
#include <ocl/allocator_op.hpp>

/// @brief Basic Send test
int main()
{
	ocl::allocator<int> int_alloc;
	auto				foo = int_alloc.construct_array<1>();

	*foo = 67;
    ocl::io::print(*foo);

	return EXIT_SUCCESS;
}
