#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "mem/gbmemory.h"
#include "cpu/cpuregisters.h"


using namespace std;

TEST(CpuTest, testClock) {
  auto mem = std::make_shared<GBMemory>();
  auto reg = std::make_unique<CpuRegisters>();
  auto cpu = Cpu(std::move(reg), mem);
  ASSERT_NO_THROW(cpu.clock(););
}


