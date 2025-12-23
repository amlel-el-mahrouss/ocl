// File: allocator.test.cpp
// Purpose; Allocator test for OCL.
/// @brief This unit test checks if the test succeeds.
/// @author Amlal El Mahrouss

#include <ocl/allocator_op.hpp>

#define BOOST_TEST_MODULE allocator_op
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( allocator_should_succeed )
{
    auto ptr = ocl::allocator<int>{}.construct_array<10>();
    int* arr = ptr.get();
    BOOST_TEST( arr != nullptr );
}
