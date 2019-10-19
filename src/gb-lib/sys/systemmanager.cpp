#include "systemmanager.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "location/location.h"
#include "cpu/flagsview.h"


SystemManager::SystemManager(IMemoryViewSP memory)
  : memory_(memory)
  , cpu_(std::make_unique<Cpu>(std::make_unique<CpuRegisters>(), memory_))
{
}

SystemManager::~SystemManager()
{
}

void SystemManager::clock()
{
  cpu_->clock();
}
