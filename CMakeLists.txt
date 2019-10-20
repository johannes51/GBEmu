cmake_minimum_required(VERSION 3.2)
project(GBE)

set(PROJECT_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(src)
add_subdirectory(test)


