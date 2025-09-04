
cmake_minimum_required(VERSION 3.15...3.31)

project(
	Alloc
  VERSION 1.0
  LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS container)

add_executable(Alloc allocator_system.cc)

target_link_libraries(Alloc PRIVATE Boost::container)

set_property(TARGET Alloc PROPERTY CXX_STANDARD 20)
target_include_directories(Alloc PUBLIC ../../)
