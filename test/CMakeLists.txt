cmake_minimum_required(VERSION 3.2)
project(gbe_tests)

find_package(GTest REQUIRED)
include(GoogleTest)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/res/Tetris.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/Tetris.gb"
  COPYONLY)
configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/res/jumps_calls.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/jumps_calls.gb"
  COPYONLY)
configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/res/loads.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/loads.gb"
  COPYONLY)

set(TEST_SOURCES
  main.cpp
  gbelib_tests/cpu/cpu_tests.cpp
  gbelib_tests/cpu/cpuflags_tests.cpp
  gbelib_tests/cpu/cpuregisters_tests.cpp
  gbelib_tests/cpu/id/arithmetic_tests.cpp
  gbelib_tests/cpu/id/instructiondecoder_tests.cpp
  gbelib_tests/cpu/id/jumps_calls_tests.cpp
  gbelib_tests/cpu/id/loads_tests.cpp
  gbelib_tests/cpu/id/opcodeview_tests.cpp
  gbelib_tests/cpu/operation/aluoperation_tests.cpp
  gbelib_tests/cpu/operation/jump_tests.cpp
  gbelib_tests/cpu/operation/wordload_tests.cpp
  gbelib_tests/cpu/operation/byteload_tests.cpp
  gbelib_tests/cpu/operation/nop_tests.cpp
  gbelib_tests/location/location_tests.cpp
  gbelib_tests/location/locationimpl_tests.cpp
  gbelib_tests/location/nullbyte_tests.cpp
  gbelib_tests/location/rambyte_tests.cpp
  gbelib_tests/location/rombyte_tests.cpp
  gbelib_tests/location/zerobyte_tests.cpp
  gbelib_tests/gb/gbmemoryfactory_tests.cpp
  gbelib_tests/mem/nullbank_tests.cpp
  gbelib_tests/mem/memorymanifold_tests.cpp
  gbelib_tests/mem/memoryarea_tests.cpp
  gbelib_tests/mem/memtools_tests.cpp
  gbelib_tests/mem/mirrorbank_tests.cpp
  gbelib_tests/mem/rambank_tests.cpp
  gbelib_tests/mem/rombank_tests.cpp
  gbelib_tests/util/helpers_tests.cpp
  gbelib_tests/util/ops_tests.cpp
  gbelib_tests/sys/systemmanager_tests.cpp
  )

add_executable(gbelib_tests ${TEST_SOURCES})
target_link_libraries(gbelib_tests PRIVATE gbelib GTest::GTest GTest::Main)
target_include_directories(gbelib_tests PRIVATE $<TARGET_PROPERTY:gbelib,INCLUDE_DIRECTORIES>)

target_include_directories(gbelib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
enable_wall(gbelib_tests)
enable_effcpp(gbelib_tests)
cxx_17(gbelib_tests)
clang_format(format_gbelib_tests gbelib_tests)

target_code_coverage(gbelib_tests)

install(TARGETS gbelib_tests DESTINATION bin)
