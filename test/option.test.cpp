// File: option.test.cpp
// Purpose; Option test for OCL.
/// @brief This unit test checks if the unit test fails with the expected value.
/// @author Amlal El Mahrouss

#include <ocl/option.hpp>

#define BOOST_TEST_MODULE option
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( option_should_fail )
{
  bool ret = false;
  try {
    ocl::option opt(ocl::eval_false());
    opt.expect("");
  } catch (...) {
    ret = true;
  }
  BOOST_TEST( ret == true );
}

BOOST_AUTO_TEST_CASE( option_should_succeed )
{
  bool ret = true;
  try {
    ocl::option opt(ocl::eval_true());
    opt.expect("");
  } catch (...) {
    ret = false;
  }
  BOOST_TEST( ret == true );
}