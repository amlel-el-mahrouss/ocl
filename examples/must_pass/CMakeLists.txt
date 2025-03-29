
cmake_minimum_required(VERSION 3.15...3.31)

project(
  MustPass
  VERSION 1.0
  LANGUAGES CXX)

add_executable(MustPass must_pass.cc)

set_property(TARGET MustPass PROPERTY CXX_STANDARD 20)
target_include_directories(MustPass PUBLIC ../../lib)
