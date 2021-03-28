cmake_minimum_required(VERSION 3.11)

message("${CMAKE_CURRENT_LIST_DIR}/../res/Tetris.gb")
message("${CMAKE_CURRENT_LIST_DIR}/../res/Tetris.gb")
configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/../res/Tetris.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/Tetris.gb"
  COPYONLY)
configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/../res/jumps_calls.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/jumps_calls.gb"
  COPYONLY)
configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/../res/loads.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/loads.gb"
  COPYONLY)

set(TEST_SOURCES
  cpu/cpu_tests.cpp
  cpu/cpuflags_tests.cpp
  cpu/cpuregisters_tests.cpp
  cpu/id/arithmetic_tests.cpp
  cpu/id/instructiondecoder_tests.cpp
  cpu/id/jumps_calls_tests.cpp
  cpu/id/loads_tests.cpp
  cpu/id/opcodeview_tests.cpp
  cpu/operation/aluoperation_tests.cpp
  cpu/operation/jump_tests.cpp
  cpu/operation/wordload_tests.cpp
  cpu/operation/byteload_tests.cpp
  cpu/operation/nop_tests.cpp
  location/location_tests.cpp
  location/locationimpl_tests.cpp
  location/nullbyte_tests.cpp
  location/rambyte_tests.cpp
  location/rombyte_tests.cpp
  location/zerobyte_tests.cpp
  gb/gbmemoryfactory_tests.cpp
  gb/cartloader_tests.cpp
  mem/nullbank_tests.cpp
  mem/memorymanifold_tests.cpp
  mem/memoryarea_tests.cpp
  mem/memtools_tests.cpp
  mem/mirrorbank_tests.cpp
  mem/rambank_tests.cpp
  mem/rombank_tests.cpp
  mock/variablebyte.h
  mock/variablebyte.cpp
  util/helpers_tests.cpp
  util/ops_tests.cpp
  sys/systemmanager_tests.cpp
  )

add_executable(gbelib_tests ${TEST_SOURCES})
target_link_libraries(gbelib_tests PRIVATE gbelib GTest::GTest GTest::Main)
target_include_directories(gbelib_tests PRIVATE $<TARGET_PROPERTY:gbelib,INCLUDE_DIRECTORIES>)
target_include_directories(gbelib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
get_target_property(gtest_include_dirs GTest::GTest INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(gbelib_tests SYSTEM PRIVATE ${gtest_include_dirs})

gtest_add_tests(TARGET gbelib_tests)
add_dependencies(tests gbelib_tests)

enable_wall(gbelib_tests)
enable_effcpp(gbelib_tests)
cxx_17(gbelib_tests)
clang_format(format_gbelib_tests gbelib_tests)
clang_tidy(gbelib_tests)

target_code_coverage(gbelib_tests)

install(TARGETS gbelib_tests DESTINATION bin)
