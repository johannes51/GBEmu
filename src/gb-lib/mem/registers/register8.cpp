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

void Register8::set(const uint8_t& value)
{
  buffer_ = upper_ ? static_cast<uint16_t>(
                         static_cast<unsigned>(buffer_ & LOWER_BYTE_MASK) | static_cast<unsigned>(value << BYTE_SHIFT))
                   : static_cast<uint16_t>(static_cast<unsigned>(buffer_ & UPPER_BYTE_MASK) | value);
}
