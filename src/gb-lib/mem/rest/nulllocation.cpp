#include "nulllocation.h"

#include <stdexcept>

auto NullLocation::get() const -> const uint8_t& { throw std::logic_error("Read on null byte"); }

void NullLocation::set(const uint8_t& value)
{
  (void)value;
  throw std::logic_error("Write on null byte");
}
