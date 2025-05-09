#include "memoryregisteradapter.h"

#include "location/location8.h"
#include "util/helpers.h"

MemoryRegisterAdapter::MemoryRegisterAdapter(IMemoryViewSP mem, address_type address)
    : mem_(std::move(mem))
    , address_(address)
{
}

auto MemoryRegisterAdapter::get() const -> uint8_t { return mem_->getLocation8(address_)->get(); }

void MemoryRegisterAdapter::set(uint8_t value) { *mem_->getLocation8(address_) = value; }

auto MemoryRegisterAdapter::testBit(uint8_t pos) const -> bool
{
  return hlp::checkBit(mem_->getLocation8(address_)->get(), pos);
}

void MemoryRegisterAdapter::setBit(uint8_t pos, bool value)
{
  auto temp = get();
  if (value) {
    hlp::setBit(temp, pos);
  } else {
    hlp::clearBit(temp, pos);
  }
  set(temp);
}
