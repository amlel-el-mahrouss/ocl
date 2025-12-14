#include <ocl/crc_hash.hpp>
#include <ocl/print.hpp>
#include <ocl/option.hpp>

int main(int argc, char** argv)
{
    ocl::option opt{ocl::eval_eq(nullptr, nullptr)};
    opt.expect("is incorrect");

	return 0;
}
