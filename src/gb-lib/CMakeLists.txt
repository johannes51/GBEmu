cmake_minimum_required(VERSION 3.2)
project(division C CXX)

set(SOURCE_FILES
    cpu/cpu.h
    cpu/cpu.cpp
    cpu/cpu_defines.h
    cpu/cpuflags.h
    cpu/cpuflags.cpp
    cpu/flagsview.h
    cpu/flagsview.cpp
    cpu/gbregisters.h
    cpu/gbregisters.cpp
    cpu/operation.h
    cpu/operation.cpp
    cpu/register_flags.h
    cpu/registersinterface.h
    debug/simplelocation.h
    debug/simplelocation.cpp
    mem/gbmemory.h
    mem/gbmemory.cpp
    mem/ramlocation.h
    mem/ramlocation.cpp
    mem/mem_defines.h
    mem/memoryview.h
    util/helpers.h
    util/helpers.cpp
    util/ops.h
    util/ops.cpp
    util/location.h
    util/location.cpp
    util/locationbyte.h
    util/locationbyte.cpp
    util/locationimpl.h
    util/locationimpl.cpp
    sys/systemmanager.h
    sys/systemmanager.cpp
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_definitions(-DDEBUG)
endif()

add_library(gbelib SHARED STATIC ${SOURCE_FILES})

target_include_directories(gbelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS gbelib DESTINATION ${PROJECT_INSTALL_LIB_DIR})
