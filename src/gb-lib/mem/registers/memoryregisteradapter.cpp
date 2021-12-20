#include "memoryregisteradapter.h"

#include "location/location.h"

MemoryRegisterAdapter::MemoryRegisterAdapter(IMemoryViewSP mem, address_type address)
    : mem_(std::move(mem))
    , address_(address)
{
}

uint8_t MemoryRegisterAdapter::get() const
{
  return mem_->getByte(address_).get();
}

auto MemoryRegisterAdapter::testBit(uint8_t pos) const -> bool
{
  return (mem_->getByte(address_).get() & (1U << pos)) > 0;
}

