#include "register8.h"

#include "constants.h"

Register8::Register8(uint16_t& buffer, bool upper)
    : Location8()
    , buffer_(buffer)
    , upper_(upper)
{
}

auto Register8::getReference() -> uint8_t&
{
  return *(upper_ ? reinterpret_cast<uint8_t*>(&buffer_) + 1 : reinterpret_cast<uint8_t*>(&buffer_));
}

auto Register8::get() const -> const uint8_t&
{
  return *(upper_ ? reinterpret_cast<uint8_t*>(&buffer_) + 1 : reinterpret_cast<uint8_t*>(&buffer_));
}

auto Register8::operator=(const uint8_t& rhs) -> Register8&
{
  buffer_ = upper_
      ? (static_cast<unsigned int>(buffer_ & MASK_LOWER_BYTE) | static_cast<unsigned int>(rhs << BYTE_SHIFT))
      : (static_cast<unsigned int>(buffer_ & MASK_UPPER_BYTE) | rhs);
  return *this;
}
