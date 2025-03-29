# STDX (Standard eXtended)

[![License: GPL-2.0](https://img.shields.io/badge/license-GPL--2.0-blue.svg)](LICENSE)

## Getting Started:

Here is an example of how stdx::opt works.

```cpp
#include <stdx.hpp>

int main(int argc, char** argv)
{
  auto opt = stdx::opt(stdx::eval_eq(50, 50)).expect("stdex::eval_eq, does not match!");
  opt = stdx::opt(stdx::eval_eq(50, 40));
  opt.expect("this time it doesn't.");
  
  return 0;
}
```

# Licensed under GPL-2
