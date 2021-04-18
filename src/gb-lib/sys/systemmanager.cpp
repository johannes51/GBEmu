#include "systemmanager.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "peripherals/peripheral.h"

SystemManager::SystemManager(IMemoryViewSP memory, std::unique_ptr<Cpu> cpu, std::vector<PeripheralSP> peripherals)
    : memory_(std::move(memory))
    , cpu_(std::move(cpu))
    , peripherals_(std::move(peripherals))
{
}

SystemManager::~SystemManager() = default;

void SystemManager::clock() const
{
  cpu_->clock();
  for (const auto& peri : peripherals_) {
    peri->clock();
  }
}
