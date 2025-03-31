# Amlal's Standard Extended

[![License: GPL-2.0](https://img.shields.io/badge/license-GPL--2.0-blue.svg)](LICENSE)

## Getting Started:

Here is an example of how astdx::opt works.

```cpp
#include <astdx/opt.hpp>

int main(int argc, char** argv)
{
  auto opt = astdx::opt(astdx::eval_eq(50, 50)).expect("stdex::eval_eq, does not match!");
  opt = astdx::opt(astdx::eval_eq(50, 40));
  opt.expect("this time it doesn't.");
  
  return 0;
}
```

# Licensed under GPL-2
