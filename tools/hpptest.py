#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# HPPTEST: Header-only C++ library test runner.
# Written by Amlal El Mahrouss.
# Licensed under the Boost Software License

import sys, os

COMPILER="clang++"
INCLUDE_DIR="./dev/"
CXX_STD="c++20"

if __name__ == '__main__':
    if len(sys.argv) == 3:
        ret = os.system(f"{COMPILER} -I{INCLUDE_DIR} -I{sys.argv[2]} -std={CXX_STD} -DOCL_HPPTEST '-DOCL_HPPTEST_ASSERT(x)=static_assert(x, #x)' {sys.argv[1]}")
        if ret == 0:
            print("[HPPTEST] HPPTEST PASSES.")

