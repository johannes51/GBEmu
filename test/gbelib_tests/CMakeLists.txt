cmake_minimum_required(VERSION 3.11)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/../res/instr_timing.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/instr_timing.gb"
  COPYONLY)
configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/../res/cpu_instrs.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/cpu_instrs.gb"
  COPYONLY)
configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/../res/mem_timing.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/mem_timing.gb"
  COPYONLY)
configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/../res/mem_timing2.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/mem_timing2.gb"
  COPYONLY)
configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/../res/interrupt_time.gb"
  "${CMAKE_CURRENT_BINARY_DIR}/interrupt_time.gb"
  COPYONLY)

set(TEST_SOURCES
  # apu/apu_tests.cpp
  # apu/gbchannel1_tests.cpp
  # apu/gbchannel2_tests.cpp
  # apu/gbchannel3_tests.cpp
  # apu/gbchannel4_tests.cpp
  # apu/gbmixer_tests.cpp
  # apu/channel_util/dac_tests.cpp
  # apu/channel_util/envelope_tests.cpp
  # apu/channel_util/gbpulsechannel_tests.cpp
  # apu/channel_util/length_tests.cpp
  # apu/channel_util/lengthch3_tests.cpp
  # apu/channel_util/period_tests.cpp
  # apu/channel_util/sweep_tests.cpp
  cpu/cpu_tests.cpp
  cpu/id/baseinstructiondecoder_tests.cpp
  cpu/id/basicrotatedecoder_tests.cpp
  cpu/id/bytearithmeticdecoder_tests.cpp
  cpu/id/byteloadsdecoder_tests.cpp
  cpu/id/cbopdecoder_tests.cpp
  cpu/id/controldecoder_tests.cpp
  cpu/id/jumpscallsdecoder_tests.cpp
  cpu/id/miscarithmeticdecoder_tests.cpp
  cpu/id/opcodeview_tests.cpp
  cpu/id/unimplementeddecoder_tests.cpp
  cpu/id/wordarithmeticdecoder_tests.cpp
  cpu/id/wordloadsdecoder_tests.cpp
  cpu/operation/basicrotate_tests.cpp
  cpu/operation/bytealuoperation_tests.cpp
  cpu/operation/byteloadoperation_tests.cpp
  cpu/operation/cbop_tests.cpp
  cpu/operation/cbprefix_tests.cpp
  cpu/operation/controloperation_tests.cpp
  cpu/operation/operation_tests.cpp
  cpu/operation/jump_tests.cpp
  cpu/operation/miscarithmetic_tests.cpp
  cpu/operation/pushpop_tests.cpp
  cpu/operation/wordaluoperation_tests.cpp
  cpu/operation/wordload_tests.cpp
  cpu/registers/cpuflags_tests.cpp
  cpu/registers/cpuregisters_tests.cpp
  cpu/registers/register8_tests.cpp
  cpu/registers/register16_tests.cpp
  gb/gbmemoryfactory_tests.cpp
  gb/cartloader_tests.cpp
  io/divregister_tests.cpp
  mem/location_tests.cpp
  mem/ramlocation_tests.cpp
  mem/romlocation_tests.cpp
  mem/variablelocation_tests.cpp
  mem/zerolocation_tests.cpp
  mem/memoryarea_tests.cpp
  mem/memtools_tests.cpp
  mem/mirrorbank_tests.cpp
  mem/rambank_tests.cpp
  mem/rombank_tests.cpp
  mem/zerobank_tests.cpp
  ops/arithmetic_tests.cpp
  ops/bitmanip_tests.cpp
  ops/logic_tests.cpp
  ops/ops_tests.cpp
  ops/shiftrotate_tests.cpp
  peripherals/gbinterrupthandler_tests.cpp
  peripherals/gbtimer_tests.cpp
  # ppu/gbrenderer_tests.cpp
  ppu/pixelbuffer_tests.cpp
  # ppu/ppu_tests.cpp
  ppu/layer/gbbg_tests.cpp
  ppu/layer/gbobjects_tests.cpp
  ppu/layer/gbwindow_tests.cpp
  ppu/layer/helper_tests.cpp
  ppu/layer/palette_tests.cpp
  ppu/layer/tile_tests.cpp
  ppu/layer/tiledata_tests.cpp
  ppu/layer/tilemap_tests.cpp
  roms/cpu_instrs_tests.cpp
  roms/instr_timing_tests.cpp
  roms/interrupt_time_tests.cpp
  roms/mem_timing_tests.cpp
  roms/mem_timing2_tests.cpp
  sys/systemmanager_tests.cpp
  util/helpers_tests.cpp
  util/fallingedgedetector_tests.cpp
)

set(MOCK_SOURCES
  mock/mockbytelocationadapter.h
  mock/mockchannel.h
  mock/mockflags.h
  mock/mockinterrupthandler.h
  mock/mockiobank.h
  mock/mockmixer.h
  mock/mockoam.h
  mock/mockregisteradapter.h
  mock/mockregisters.h
  mock/mockregisters.cpp
  mock/mockrenderer.h
  mock/mocktiledata.h
  mock/mocktiledata.cpp
  mock/mocktilemap.h
  mock/mocktilemap.cpp
  mock/testbank.h
  mock/testbank.cpp
)

add_executable(gbelib_tests ${TEST_SOURCES} ${MOCK_SOURCES})
target_link_libraries(gbelib_tests PRIVATE gbelib GTest::GTest GTest::Main GTest::gmock)
target_include_directories(gbelib_tests PRIVATE $<TARGET_PROPERTY:gbelib,INCLUDE_DIRECTORIES>)
target_include_directories(gbelib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
get_target_property(gtest_include_dirs GTest::GTest INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(gbelib_tests SYSTEM PRIVATE ${GTEST_INCLUDE_DIRS})

gtest_add_tests(TARGET gbelib_tests)
add_dependencies(tests gbelib_tests)

enable_wall(gbelib_tests)
cxx_20(gbelib_tests)
clang_format(format_gbelib_tests gbelib_tests)
clang_tidy(gbelib_tests)

if(CMAKE_BUILD_TYPE MATCHES "[Cc][Oo][Vv][Ee][Rr][Aa][Gg][Ee]")
  target_code_coverage(gbelib_tests EXCLUDE ${TEST_SOURCES} ${TEST_SOURCES_EXTERNAL} ${MOCK_SOURCES})
endif()

install(TARGETS gbelib_tests DESTINATION bin)
