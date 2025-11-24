
cmake_minimum_required(VERSION 3.15...3.31)

project(
  Equiv
  VERSION 1.0
  LANGUAGES CXX)

add_executable(Equiv equiv.cc)

set_property(TARGET Equiv PROPERTY CXX_STANDARD 20)
target_include_directories(Equiv PUBLIC ../../include/ocl)
