#include "registerbuffer.h"

RegisterBuffer::RegisterBuffer(uint8_t initial)
    : value_(initial)
{
}

auto RegisterBuffer::get() const -> uint8_t { return value_; }

void RegisterBuffer::set(uint8_t value) { value_ = value; }

auto RegisterBuffer::testBit(uint8_t pos) const -> bool { return test_bit(value_, pos); }

void RegisterBuffer::setBit(uint8_t pos, bool value)
{
  if (value) {
    set_bit(value_, pos);
  } else {
    reset_bit(value_, pos);
  }
}
