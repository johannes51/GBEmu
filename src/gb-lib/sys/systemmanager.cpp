#include "systemmanager.h"

#include "cpu/cpu.h"

SystemManager::SystemManager(std::unique_ptr<Cpu> cpu, std::vector<TickableSP> peripherals, const GbPixelBuffer* buffer)
    : cpu_(std::move(cpu))
    , peripherals_(std::move(peripherals))
    , buffer_(buffer)
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

auto SystemManager::getBuffer() const -> const GbPixelBuffer* { return buffer_; }
