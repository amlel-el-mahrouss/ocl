cmake_minimum_required(VERSION 3.10)
project(TrackedPtrTestBasic)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(TrackedPtrTestBasic tracked_ptr_test.cc)
target_link_libraries(TrackedPtrTestBasic gtest_main)

set_property(TARGET TrackedPtrTestBasic PROPERTY CXX_STANDARD 20)
target_include_directories(TrackedPtrTestBasic PUBLIC ../../)

include(GoogleTest)
gtest_discover_tests(TrackedPtrTestBasic)
