#include "systemmanager.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "mem/gbmemory.h"
#include "mem/memoryview.h"
#include "util/location.h"
#include "cpu/flagsview.h"


SystemManager::SystemManager()
  : mem_(std::make_unique<GBMemory>())
  , cpu_(std::make_unique<Cpu>(std::make_unique<CpuRegisters>(), mem_))
{
}

SystemManager::~SystemManager()
{
}

void SystemManager::clock()
{
  cpu_->clock();
}
