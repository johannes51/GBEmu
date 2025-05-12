cmake_minimum_required(VERSION 3.11)

find_package(GTest REQUIRED)
include(GoogleTest)

add_custom_target(tests)
include_directories(
  ${GTEST_INCLUDE_DIRS}
  ${GMOCK_INCLUDE_DIRS}
)

enable_testing()

add_subdirectory(gbelib_tests)
add_subdirectory(gb-doc)
