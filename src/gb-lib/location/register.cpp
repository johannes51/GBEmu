#include "register.h"

#include "constants.h"

Register::Register(uint16_t& buffer, bool upper)
    : Location(Type::Both)
    , buffer_(buffer)
    , upper_(upper)
{
}

auto Register::getReference() -> uint8_t&
{
  return *(upper_ ? reinterpret_cast<uint8_t*>(&buffer_) + 1 : reinterpret_cast<uint8_t*>(&buffer_));
}

auto Register::getByte() const -> const uint8_t&
{
  return *(upper_ ? reinterpret_cast<uint8_t*>(&buffer_) + 1 : reinterpret_cast<uint8_t*>(&buffer_));
}

auto Register::getWord() const -> const uint16_t& { return buffer_; }

auto Register::operator=(const uint8_t& rhs) -> Register&
{
  buffer_ = upper_
      ? (static_cast<unsigned int>(buffer_ & MASK_LOWER_BYTE) | static_cast<unsigned int>(rhs << BYTE_SHIFT))
      : (static_cast<unsigned int>(buffer_ & MASK_UPPER_BYTE) | rhs);
  return *this;
}

auto Register::operator=(const uint16_t& rhs) -> Register&
{
  buffer_ = rhs;
  return *this;
}
