#include "systemmanager.h"

#include "cpu/cpu.h"
#include "cpu/gbregisters.h"
#include "mem/gbmemory.h"
#include "mem/memoryview.h"


SystemManager::SystemManager()
  : mem_(std::make_unique<GBMemory>())
  , cpu_(std::make_unique<Cpu>(std::make_unique<GBRegisters>(), mem_))
{
}

SystemManager::~SystemManager()
{
}

void SystemManager::clock()
{
  cpu_->clock();
}
