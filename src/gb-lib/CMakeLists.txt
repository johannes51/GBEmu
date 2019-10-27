cmake_minimum_required(VERSION 3.2)
project(gb-lib C CXX)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(gbelib SHARED STATIC)
target_sources(gbelib PRIVATE
  defines.h
  cpu/cpu.h
  cpu/cpu.cpp
  cpu/cpu_defines.h
  cpu/cpuflags.h
  cpu/cpuflags.cpp
  cpu/cpuregisters.h
  cpu/cpuregisters.cpp
  cpu/flagsview.h
  cpu/registername.h
  cpu/registersinterface.h
  cpu/id/arithmetic.h
  cpu/id/arithmetic.cpp
  cpu/id/instructiondecoder.h
  cpu/id/instructiondecoder.cpp
  cpu/id/jumps_calls.h
  cpu/id/jumps_calls.cpp
  cpu/id/loads.h
  cpu/id/loads.cpp
  cpu/id/opcodeview.h
  cpu/id/opcodeview.cpp
  cpu/operation/aluoperation.h
  cpu/operation/aluoperation.cpp
  cpu/operation/operation.h
  cpu/operation/operation.cpp
  cpu/operation/jump.h
  cpu/operation/jump.cpp
  cpu/operation/load.h
  cpu/operation/load.cpp
  cpu/operation/nop.h
  cpu/operation/nop.cpp
  cpu/operation/singleop.h
  cpu/operation/singleop.cpp
  debug/variablebyte.h
  debug/variablebyte.cpp
  gb_factories/cartloader.h
  gb_factories/cartloader.cpp
  gb_factories/gb_defines.h
  gb_factories/memoryfactory.h
  gb_factories/memoryfactory.cpp
  mem/imemoryview.h
  mem/imemorymanager.h
  mem/mem_defines.h
  mem/memoryarea.h
  mem/memoryarea.cpp
  mem/mirrorbank.h
  mem/mirrorbank.cpp
  mem/memorymanifold.h
  mem/memorymanifold.cpp
  mem/mem_tools.h
  mem/mem_tools.cpp
  mem/nullbank.h
  mem/nullbank.cpp
  mem/rambank.h
  mem/rambank.cpp
  mem/rombank.h
  mem/rombank.cpp
  mem/singleareamanager.h
  mem/singleareamanager.cpp
  location/bufferbyte.h
  location/bufferbyte.cpp
  location/location.h
  location/location.cpp
  location/location_defines
  location/locationbyte.h
  location/locationimpl.h
  location/locationimpl.cpp
  location/nullbyte.h
  location/nullbyte.cpp
  location/rambyte.h
  location/rambyte.cpp
  location/registerbyte.h
  location/registerbyte.cpp
  location/rombyte.h
  location/rombyte.cpp
  location/zerobyte.h
  location/zerobyte.cpp
  util/helpers.h
  util/helpers.cpp
  util/ops.h
  util/ops.cpp
  sys/systemmanager.cpp
  sys/systemmanager.h
  )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/script;")
include(compiler-options)
include(c++-standards)
include(doxygen)
include(formatting)
include(tools)
include(sanitizers)

set_target_properties(gbelib PROPERTIES PUBLIC_HEADER "systemmanager.h")
target_include_directories(gbelib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
enable_wall(gbelib)
enable_effcpp(gbelib)
cxx_17(gbelib)
clang_format(format_gbelib gbelib)
clang_tidy(gbelib "-checks=*,-clang-diagnostic-unused-parameter,\
-fuchsia-default-arguments-calls,-fuchsia-overloaded-operator,\
-modernize-use-trailing-return-type,-misc-unused-parameters,-readability-redundant-member-init,\
-readability-magic-numbers,-cppcoreguidelines-avoid-magic-numbers")
cppcheck(gbelib)
#sanitize(gbelib "Address")

build_docs()

install(TARGETS gbelib
  ARCHIVE DESTINATION CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  PUBLIC_HEADER DESTINATION include/gbelib
  )
