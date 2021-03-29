#include "systemmanager.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"

SystemManager::SystemManager(IMemoryViewSP memory, std::unique_ptr<Cpu> cpu)
    : memory_(std::move(memory))
    , cpu_(std::move(cpu))
{
}

SystemManager::~SystemManager() = default;

void SystemManager::clock() const { cpu_->clock(); }
