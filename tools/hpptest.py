#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# HPPTEST: Header-only C++ library test runner.
# Author: Amlal El Mahrouss.
# License Boost Software License 1.0

import sys, os

CXX_COMPILER="clang++"
CXX_INCLUDE_DIR="./include/"
CXX_STD="c++20"

# Runs a simple compilation command to check if the test passes or not.
if __name__ == '__main__':
    if len(sys.argv) == 3:
        ret = os.system(f"{CXX_COMPILER} -I{CXX_INCLUDE_DIR} -I{sys.argv[2]} -std={CXX_STD} -DOCL_HPPTEST '-DOCL_HPPTEST_ASSERT(x)=static_assert(x, #x)' {sys.argv[1]}")
        if ret == 0:
            print("[HPPTEST] TEST PASS.")
        else:
            print(f"[HPPTEST] TEST FAILED: RETURN CODE: {ret}")
            print(f"COMMAND: {CXX_COMPILER} -I{CXX_INCLUDE_DIR} -I{sys.argv[2]} -std={CXX_STD} -DOCL_HPPTEST '-DOCL_HPPTEST_ASSERT(x)=static_assert(x, #x)' {sys.argv[1]}")
