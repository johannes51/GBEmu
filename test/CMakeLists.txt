cmake_minimum_required(VERSION 3.2)
project(divider_tests)

find_package(GTest REQUIRED)
include(GoogleTest)

include_directories(${DIVISION_HEADERS_DIR})

set(SOURCE_FILES
  main.cpp
  gbelib_tests/cpu/cpu_tests.cpp
  gbelib_tests/cpu/operation_tests.cpp
  gbelib_tests/cpu/cpuflags_tests.cpp
  gbelib_tests/cpu/cpuregisters_tests.cpp
  gbelib_tests/cpu/registerbyte_tests.cpp
  gbelib_tests/location/location_tests.cpp
  gbelib_tests/location/locationimpl_tests.cpp
  gbelib_tests/location/nullbyte_tests.cpp
  gbelib_tests/location/ramlocation_tests.cpp
  gbelib_tests/gb/gbmemoryfactory_tests.cpp
  gbelib_tests/mem/nullbank_tests.cpp
  gbelib_tests/mem/mirrorbank_tests.cpp
  gbelib_tests/mem/rambank_tests.cpp
  gbelib_tests/util/helpers_tests.cpp
  gbelib_tests/util/ops_tests.cpp
  gbelib_tests/sys/systemmanager_tests.cpp
)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/gbelib_tests/gb/Tetris.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/Tetris.gb"
  COPYONLY)

add_executable(gbelib_tests ${SOURCE_FILES})
target_link_libraries(gbelib_tests gbelib gtest gtest_main pthread)
install(TARGETS gbelib_tests DESTINATION bin)

