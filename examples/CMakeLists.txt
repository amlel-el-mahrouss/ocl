
cmake_minimum_required(VERSION 3.15...3.31)

project(
  StrCheckusm
  VERSION 1.0
  LANGUAGES CXX)

add_executable(StrCheckusm str_checksum.cc)

set_property(TARGET StrCheckusm PROPERTY CXX_STANDARD 20)
target_include_directories(StrCheckusm PUBLIC ../lib)
