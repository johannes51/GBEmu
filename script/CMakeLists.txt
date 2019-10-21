cmake_minimum_required(VERSION 3.2)
project(script)

add_custom_target(script SOURCES
  compiler-options.cmake
  c++-standards.cmake
  dependency-graph.cmake
  doxygen.cmake
  formatting.cmake
  sanitizers.cmake
  tools.cmake
  )

