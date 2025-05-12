cmake_minimum_required(VERSION 3.11)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/roms/01-special.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/01.gb"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/roms/02-interrupts.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/02.gb"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/roms/03-op sp,hl.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/03.gb"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/roms/04-op r,imm.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/04.gb"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/roms/05-op rp.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/05.gb"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/roms/06-ld r,r.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/06.gb"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/roms/07-jr,jp,call,ret,rst.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/07.gb"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/roms/08-misc instrs.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/08.gb"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/roms/09-op r,r.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/09.gb"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/roms/10-bit ops.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/10.gb"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/roms/11-op a,(hl).gb"
  "${CMAKE_CURRENT_BINARY_DIR}/11.gb"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/gbdoc.sh"
  "${CMAKE_CURRENT_BINARY_DIR}/gbdoc.sh"
  COPYONLY)

set(GB_DOC_SRCS
  "${CMAKE_CURRENT_LIST_DIR}/gbdoc.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/gbdoc.sh"
)

add_custom_target(test-gbdoc)

add_custom_target(copy-gbdoc
  COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
  "${CMAKE_CURRENT_SOURCE_DIR}/repo/"
  "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "Copying data"
)

add_executable(make-gbdoc-tests)
target_sources(make-gbdoc-tests PRIVATE ${GB_DOC_SRCS})
target_link_libraries(make-gbdoc-tests PRIVATE gbelib)
cxx_20(make-gbdoc-tests)

add_custom_target(clean-gbdoc-tests COMMAND rm -f cpu*.txt  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_custom_target(run-gbdoc-tests COMMAND ./make-gbdoc-tests WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_dependencies(run-gbdoc-tests make-gbdoc-tests clean-gbdoc-tests)

add_custom_target(eval-gbdoc-tests COMMAND ./gbdoc.sh WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_dependencies(eval-gbdoc-tests run-gbdoc-tests copy-gbdoc)
add_dependencies(test-gbdoc eval-gbdoc-tests)
