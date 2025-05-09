#include "nulllocation.h"

#include <stdexcept>

NullLocation::NullLocation()
    : Location8()
{
}

auto NullLocation::get() const -> const uint8_t& { throw std::logic_error("Read on null byte"); }

auto NullLocation::operator=(const uint8_t& rhs) -> NullLocation&
{
  (void)rhs;
  throw std::logic_error("Write on null byte");
}
