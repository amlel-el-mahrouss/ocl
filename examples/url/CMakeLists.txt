
cmake_minimum_required(VERSION 3.15...3.31)

project(
  Url
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS container)

add_executable(Url fix.cc)

set_property(TARGET Url PROPERTY CXX_STANDARD 20)
target_include_directories(Url PUBLIC ../../include/ocl)
target_link_libraries(Url PRIVATE Boost::container)
