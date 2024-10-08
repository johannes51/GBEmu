#include "register.h"

Register::Register(uint16_t& buffer, bool upper)
    : Location(Type::Both)
    , buffer_(buffer)
    , upper_(upper)
{
}

uint8_t& Register::getReference()
{
  return *(upper_ ? reinterpret_cast<uint8_t*>(&buffer_) + 1 : reinterpret_cast<uint8_t*>(&buffer_));
}

auto Register::getByte() const -> const uint8_t&
{
  return *(upper_ ? reinterpret_cast<uint8_t*>(&buffer_) + 1 : reinterpret_cast<uint8_t*>(&buffer_));
}

auto Register::getWord() const -> const uint16_t& { return buffer_; }

Register& Register::operator=(const uint8_t& rhs)
{
  buffer_ = upper_ ? ((buffer_ & 0x00FF) | (rhs << 8U)) : ((buffer_ & 0xFF00) | (rhs));
  return *this;
}

Register& Register::operator=(const uint16_t& rhs)
{
  buffer_ = rhs;
  return *this;
}
