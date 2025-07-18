
cmake_minimum_required(VERSION 3.15...3.31)

project(
  Fix
  VERSION 1.0
  LANGUAGES CXX)

add_executable(TrackedPtr tracked_ptr.cc)

set_property(TARGET TrackedPtr PROPERTY CXX_STANDARD 20)
target_include_directories(TrackedPtr PUBLIC ../../)
