
cmake_minimum_required(VERSION 3.15...3.31)

project(
  Fix
  VERSION 1.0
  LANGUAGES CXX)

add_executable(Fix fix.cc)

set_property(TARGET Fix PROPERTY CXX_STANDARD 20)
target_include_directories(Fix PUBLIC ../../include/ocl)
