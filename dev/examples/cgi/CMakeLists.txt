
cmake_minimum_required(VERSION 3.15...3.31)

project(
  CGI
  VERSION 1.0
  LANGUAGES CXX)

add_executable(CGI cgi.cc)

set_property(TARGET CGI PROPERTY CXX_STANDARD 20)
target_include_directories(CGI PUBLIC ../../)
