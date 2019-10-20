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
  cpu/flagsview.cpp
  cpu/operation.h
  cpu/operation.cpp
  cpu/register_flags.h
  cpu/registersinterface.h
  debug/simplelocation.h
  debug/simplelocation.cpp
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
  location/locationbyte.cpp
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

set_target_properties(gbelib PROPERTIES PUBLIC_HEADER "systemmanager.h")

target_include_directories(gbelib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET gbelib PROPERTY CXX_STANDARD 17)

install(TARGETS gbelib
  ARCHIVE DESTINATION CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  PUBLIC_HEADER DESTINATION include/gbelib
  )
