#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys, os

if __name__ == '__main__':
    if len(sys.argv) == 3:
        ret = os.system(f"clang++ -I./dev/ -I{sys.argv[2]} -std=c++20 -DOCL_HPPTEST '-DOCL_HPPTEST_ASSERT(x)=static_assert(x, #x)' {sys.argv[1]}")
        if ret == 0:
            print("[HPPTEST] HPPTEST PASSES.")

