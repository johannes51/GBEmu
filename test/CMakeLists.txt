cmake_minimum_required(VERSION 3.2)
project(divider_tests)

find_package(GTest REQUIRED)
include(GoogleTest)

include_directories(${DIVISION_HEADERS_DIR})

set(SOURCE_FILES
  main.cpp
  gbelib_tests/util/helpers_tests.cpp
  gbelib_tests/util/location_tests.cpp
  gbelib_tests/util/ops_tests.cpp
  gbelib_tests/sys/systemmanager_tests.cpp
)

add_executable(gbelib_tests ${SOURCE_FILES})
target_link_libraries(gbelib_tests gbelib gtest gtest_main pthread)
install(TARGETS gbelib_tests DESTINATION bin)

