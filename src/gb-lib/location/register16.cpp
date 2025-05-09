#include "register16.h"

#include "constants.h"

Register16::Register16(uint16_t& buffer)
    : Location16()
    , buffer_(buffer)
{
}

auto Register16::getReference() -> uint16_t& { return buffer_; }

auto Register16::get() const -> uint16_t { return buffer_; }

auto Register16::operator=(const uint16_t& rhs) -> Register16&
{
  buffer_ = rhs;
  return *this;
}
