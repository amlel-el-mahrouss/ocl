# Open C++ Library

[![License: BSL](https://img.shields.io/badge/license-BSL-blue.svg)](LICENSE)

## Brief:

A C++ library with additional modules for your C++ SDLC.

## Requirements:

- Boost C++ libraries (https://www.boost.org/)
- Clang (https://clang.llvm.org/)
- Git (https://git-scm.com/)

## Structure:

- `core`: Core utilities and fundamental abstractions used across OCL.
- `except`: Exception classes and error-handling helpers.
- `fix`: FIX protocol utilities and helpers for Financial Information eXchange integration.
- `io`: Input/output utilities, stream helpers, and file handling.
- `log`: Logging facilities, macros, and helpers for diagnostics.
- `memory`: Memory management utilities, allocators, and smart-pointer helpers.
- `net`: Networking utilities and lightweight socket helpers.
- `simd`: SIMD-optimized algorithms and low-level performance helpers.
- `tests`: Unit and integration tests that validate OCL components.
- `utility`: General-purpose helper functions and small algorithms.

## Examples:

### Logic Module (Option container)

```cpp
#include <lib/logic/opt.hpp>

int main(int argc, char** argv)
{
  auto opt = ocl::opt(ocl::eval_eq(50, 50)).expect("ocl::eval_eq, does not match!");
  opt = ocl::opt(ocl::eval_eq(50, 40));
  opt.expect("this time it doesn't.");

  return EXIT_SUCCESS;
}
```

##### (c) 2025 Amlal El Mahrouss, licensed under the Boost Software License.
