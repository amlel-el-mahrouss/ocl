#include <ocl/crc_hash.hpp>
#include <ocl/print.hpp>
#include <ocl/option.hpp>

struct invalid_callable {
    explicit invalid_callable() = default;
    void operator()(const char* reason)
    {
        ocl::detail::throw_runtime_error(BOOST_CURRENT_LOCATION.to_string());
    }
};

/// \brief Option Monad example
int main(int argc, char** argv)
{
    ocl::option opt{ocl::eval_eq(nullptr, nullptr)};
    opt.expect("option::incorrect");

    ocl::option opt2{ocl::eval_eq(argv, nullptr)};
    opt2.expect<invalid_callable>("option::incorrect");

	return 0;
}
