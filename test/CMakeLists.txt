cmake_minimum_required(VERSION 3.2)
project(divider_tests)

find_package(GTest REQUIRED)
include(GoogleTest)

include_directories(${DIVISION_HEADERS_DIR})

set(SOURCE_FILES main.cpp src/divider_tests.cpp)

add_executable(divider_tests ${SOURCE_FILES})
target_link_libraries(divider_tests division gtest gtest_main pthread)
install(TARGETS divider_tests DESTINATION bin)

