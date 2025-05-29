#include "ioregister.h"

#include "util/helpers.h"

IoRegister::IoRegister(uint8_t initial)
    : value_(initial)
{
}

auto IoRegister::get() const -> const uint8_t& { return value_; }

auto IoRegister::operator=(const uint8_t& rhs) -> IoRegister&
{
  value_ = rhs;
  return *this;
}

auto IoRegister::getByte() const -> const uint8_t& { return value_; }

void IoRegister::setByte(uint8_t value) { value_ = value; }

auto IoRegister::testBit(uint8_t pos) const -> bool { return hlp::checkBit(value_, pos); }

void IoRegister::setBit(uint8_t pos, bool value)
{
  if (value) {
    hlp::setBit(value_, pos);
  } else {
    hlp::clearBit(value_, pos);
  }
}
