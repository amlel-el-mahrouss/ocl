#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys, os

if __name__ == '__main__':
    if len(sys.argv) == 2:
        os.system(f"clang++ -std=c++20 -DOCL_HPPTEST '-DOCL_HPPTEST_ASSERT(x)=static_assert(x, #x)' {sys.argv[1]}")
        print("[TEST] HEADER COMPILATION PASSES")

