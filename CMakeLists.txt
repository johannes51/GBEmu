cmake_minimum_required(VERSION 3.11)
project(GBE)

set(PROJECT_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;")
include(compiler-options)
include(doxygen)
include(clang-tools)
include(profiles)
if(CMAKE_BUILD_TYPE MATCHES "[Cc][Oo][Vv][Ee][Rr][Aa][Gg][Ee]")
  include(code-coverage)
endif()


add_subdirectory(src)
add_subdirectory(test)
