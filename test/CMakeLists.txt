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
  gbelib_tests/cpu/operation/instructiondecoder_tests.cpp
  gbelib_tests/cpu/operation/loads_tests.cpp
  gbelib_tests/cpu/operation/opcodeview_tests.cpp
  gbelib_tests/cpu/operation/nop_tests.cpp
  gbelib_tests/location/location_tests.cpp
  gbelib_tests/location/locationimpl_tests.cpp
  gbelib_tests/location/nullbyte_tests.cpp
  gbelib_tests/location/rambyte_tests.cpp
  gbelib_tests/location/rombyte_tests.cpp
  gbelib_tests/location/zerobyte_tests.cpp
  gbelib_tests/location/registerbyte_tests.cpp
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

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/script;")
include(compiler-options)
include(c++-standards)
include(doxygen)
include(formatting)
include(tools)

target_include_directories(gbelib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
enable_wall(gbelib_tests)
enable_effcpp(gbelib_tests)
cxx_17(gbelib_tests)
clang_format(format_gbelib_tests gbelib_tests)

install(TARGETS gbelib_tests DESTINATION bin)
