#include "memoryregisteradapter.h"

#include "location/location.h"

MemoryRegisterAdapter::MemoryRegisterAdapter(IMemoryViewSP mem, address_type address)
    : mem_(std::move(mem))
    , address_(address)
{
}

auto MemoryRegisterAdapter::get() const -> uint8_t { return mem_->getLocation(address_)->getByte(); }

auto MemoryRegisterAdapter::testBit(uint8_t pos) const -> bool
{
  return (mem_->getLocation(address_)->getByte() & (1U << pos)) > 0;
}
