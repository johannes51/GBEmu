#include "registerbuffer.h"

#include "util/helpers.h"

RegisterBuffer::RegisterBuffer(uint8_t initial)
    : value_(initial)
{
}

auto RegisterBuffer::get() const -> uint8_t { return value_; }

void RegisterBuffer::set(uint8_t value) { value_ = value; }

auto RegisterBuffer::testBit(uint8_t pos) const -> bool { return hlp::checkBit(value_, pos); }

void RegisterBuffer::setBit(uint8_t pos, bool value)
{
  if (value) {
    hlp::setBit(value_, pos);
  } else {
    hlp::clearBit(value_, pos);
  }
}
