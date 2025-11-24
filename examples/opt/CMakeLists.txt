
cmake_minimum_required(VERSION 3.15...3.31)

project(
  Opt
  VERSION 1.0
  LANGUAGES CXX)

add_executable(Opt opt.cc)

set_property(TARGET Opt PROPERTY CXX_STANDARD 20)
target_include_directories(Opt PUBLIC ../../include/ocl)
