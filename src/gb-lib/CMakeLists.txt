cmake_minimum_required(VERSION 3.2)
project(gbelib C CXX)

set(SOURCE_FILES
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
    cpu/registerbyte.h
    cpu/registerbyte.cpp
    cpu/registersinterface.h
    debug/simplelocation.h
    debug/simplelocation.cpp
    debug/variablelocation.h
    debug/variablelocation.cpp
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
    location/rombyte.h
    location/rombyte.cpp
    location/zerobyte.h
    location/zerobyte.cpp
    util/helpers.h
    util/helpers.cpp
    util/ops.h
    util/ops.cpp
    sys/systemmanager.h
    sys/systemmanager.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_definitions(-DDEBUG)
endif()

add_library(gbelib SHARED STATIC ${SOURCE_FILES})

target_include_directories(gbelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS gbelib DESTINATION ${PROJECT_INSTALL_LIB_DIR})
