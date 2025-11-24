
cmake_minimum_required(VERSION 3.15...3.31)

project(
  CGI
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS container)

add_executable(CGI cgi.cc)

target_link_libraries(CGI PRIVATE Boost::container)

set_property(TARGET CGI PROPERTY CXX_STANDARD 20)
target_include_directories(CGI PUBLIC ../../include/ocl)
