#include "memoryregisteradapter.h"

#include "location/location.h"

MemoryRegisterAdapter::MemoryRegisterAdapter(IMemoryViewSP mem, address_type address)
    : mem_(std::move(mem))
    , address_(address)
{
}

auto MemoryRegisterAdapter::get() const -> uint8_t { return mem_->getLocation(address_)->getByte(); }

void MemoryRegisterAdapter::set(uint8_t value) { *mem_->getLocation(address_) = value; }

auto MemoryRegisterAdapter::testBit(uint8_t pos) const -> bool
{
  return test_bit(mem_->getLocation(address_)->getByte(), pos);
}

void MemoryRegisterAdapter::setBit(uint8_t pos, bool value)
{
  auto temp = get();
  if (value) {
    set_bit(temp, pos);
  } else {
    reset_bit(temp, pos);
  }
  set(temp);
}
