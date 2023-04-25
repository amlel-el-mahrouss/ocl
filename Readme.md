# Here is an example of how stdx::opt works.

```cpp
#include "stdx"

int main(int argc, char** argv)
{
  auto opt = stdx::opt(stdx::eval_eq(50, 50)).expect("stdex::eval_eq, does not match!");
  opt = stdx::opt(stdx::eval_eq(50, 40));
  opt.expect("this time it doesn't.");
  
  return 0;
}
```

# Licensed under GPL-2
