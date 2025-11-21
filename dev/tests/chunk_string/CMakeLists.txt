cmake_minimum_required(VERSION 3.27)
project(BasicChunkUsage LANGUAGES CXX)

# find_package(Boost REQUIRED COMPONENTS container)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(BasicChunkUsage chunk_test.cc)
target_link_libraries(BasicChunkUsage PRIVATE gtest_main)

set_property(TARGET BasicChunkUsage PROPERTY CXX_STANDARD 20)
target_include_directories(BasicChunkUsage PUBLIC ../../)

include(GoogleTest)
gtest_discover_tests(BasicChunkUsage)
