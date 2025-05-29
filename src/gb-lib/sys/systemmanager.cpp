#include "systemmanager.h"

#include "cpu/cpu.h"

SystemManager::SystemManager(std::unique_ptr<Cpu> cpu, IMemoryViewUP mem, CartUP cart,
    std::vector<TickableUP>&& peripherals, const GbPixelBuffer* pixBuffer, std::vector<uint8_t>&& memBuffer)
    : cpu_(std::move(cpu))
    , mem_(std::move(mem))
    , cart_(std::move(cart))
    , peripherals_(std::move(peripherals))
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
