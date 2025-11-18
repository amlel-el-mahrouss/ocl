
cmake_minimum_required(VERSION 3.15...3.31)

project(
  Fix
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS container)

add_executable(Fix fix.cc)

target_link_libraries(Fix PRIVATE Boost::container)
set_property(TARGET Fix PROPERTY CXX_STANDARD 20)
target_include_directories(Fix PUBLIC ../../)
