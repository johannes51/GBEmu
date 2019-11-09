cmake_minimum_required(VERSION 3.11)
project(GBE)

set(PROJECT_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/script;")
include(compiler-options)
include(cpp-standards)
include(doxygen)
include(formatting)
include(tools)
include(sanitizers)
set(CODE_COVERAGE ON)
include(code-coverage)
include(dependency-graph)

gen_dep_graph(png)

add_subdirectory(src)
add_subdirectory(test)

