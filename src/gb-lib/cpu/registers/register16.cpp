#include "register16.h"

Register16::Register16(uint16_t& buffer)
    : buffer_(buffer)
{
}

auto Register16::get() const -> const uint16_t& { return buffer_; }

auto Register16::operator=(const uint16_t& rhs) -> Register16&
{
  buffer_ = rhs;
  return *this;
}
