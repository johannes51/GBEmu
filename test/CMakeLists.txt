cmake_minimum_required(VERSION 3.2)
project(gbe_tests)

find_package(GTest REQUIRED)
include(GoogleTest)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/gbelib_tests/gb/Tetris.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/Tetris.gb"
  COPYONLY)

set(TEST_SOURCES
  main.cpp
  gbelib_tests/cpu/cpu_tests.cpp
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

add_executable(gbelib_tests ${TEST_SOURCES})
target_link_libraries(gbelib_tests PRIVATE gbelib GTest::GTest GTest::Main)
target_include_directories(gbelib_tests PRIVATE $<TARGET_PROPERTY:gbelib,INCLUDE_DIRECTORIES>)
install(TARGETS gbelib_tests DESTINATION bin)

