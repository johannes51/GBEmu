#include "nullbyte.h"

#include <stdexcept>

auto NullByte::get() const -> uint8_t { throw std::logic_error("Read on null byte"); }

void NullByte::set(const uint8_t& value)
{
  (void)value;
  throw std::logic_error("Write on null byte");
}
