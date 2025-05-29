#include "register8.h"

#include "constants.h"

Register8::Register8(uint16_t& buffer, bool upper)
    : buffer_(buffer)
    , upper_(upper)
{
}

auto Register8::get() const -> const uint8_t&
{
  return *(upper_ ? reinterpret_cast<uint8_t*>(&buffer_) + 1 : reinterpret_cast<uint8_t*>(&buffer_));
}

auto Register8::operator=(const uint8_t& rhs) -> Register8&
{
  buffer_ = upper_ ? static_cast<uint16_t>(
                         static_cast<unsigned>(buffer_ & LOWER_BYTE_MASK) | static_cast<unsigned>(rhs << BYTE_SHIFT))
                   : static_cast<uint16_t>(static_cast<unsigned>(buffer_ & UPPER_BYTE_MASK) | rhs);
  return *this;
}
