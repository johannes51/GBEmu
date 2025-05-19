#include "systemmanager.h"

#include "cpu/cpu.h"

SystemManager::SystemManager(std::unique_ptr<Cpu> cpu, IMemoryViewUP mem, std::vector<TickableSP> peripherals,
    std::unordered_map<PeripheralRegisters, IRegisterAdapterUP>&& periRegisters, const GbPixelBuffer* pixBuffer,
    std::vector<uint8_t>&& memBuffer)
    : cpu_(std::move(cpu))
    , mem_(std::move(mem))
    , peripherals_(std::move(peripherals))
    , periRegisters_(std::move(periRegisters))
    , pixBuffer_(pixBuffer)
    , memBuffer_(std::move(memBuffer))
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

auto SystemManager::getPixBuffer() const -> const GbPixelBuffer* { return pixBuffer_; }
