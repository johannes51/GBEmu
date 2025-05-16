#include "memoryregisteradapter.h"

#include "../location8.h"
#include "util/helpers.h"

MemoryRegisterAdapter::MemoryRegisterAdapter(ByteLocationAdapterUP bufferLocation)
    : bufferLocation_(std::move(bufferLocation))
{
}

auto MemoryRegisterAdapter::getByte() const -> const uint8_t& { return bufferLocation_->get(); }

void MemoryRegisterAdapter::setByte(const uint8_t value) { bufferLocation_->set(value); }

auto MemoryRegisterAdapter::testBit(uint8_t pos) const -> bool { return hlp::checkBit(getByte(), pos); }

void MemoryRegisterAdapter::setBit(uint8_t pos, bool value)
{
  auto temp = getByte();
  if (value) {
    hlp::setBit(temp, pos);
  } else {
    hlp::clearBit(temp, pos);
  }
  setByte(temp);
}
