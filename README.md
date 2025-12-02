# Open C++ Library

[![License: BSL](https://img.shields.io/badge/license-BSL-blue.svg)](LICENSE)

A set of containers in C++ for developers.<br/>
You use them to speed up your development cycle for C++ applications.

## Requirements:

The OCL requires the following:

- [Boost](https://www.boost.org/)
- [Clang](https://clang.llvm.org/)
- [CMake](https://cmake.org/)
- [Git](https://git-scm.com/)

### Example: The Option container

Evaluates whether an expression is passing the options.

```cpp
#include <logic/option.hpp>

int main(int argc, char** argv)
{
  auto opt = ocl::option(ocl::eval_eq(50, 50)).expect("ocl::eval_eq, does not match!");
  opt = ocl::option(ocl::eval_eq(50, 40));
  opt.expect("this time it doesn't.");

  return EXIT_SUCCESS;
}
```

##### (c) 2025 Amlal El Mahrouss, licensed under the Boost Software License.
