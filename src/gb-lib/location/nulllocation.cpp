#include "nulllocation.h"

#include <stdexcept>

NullLocation::NullLocation()
    : Location(Type::Both)
{
}

auto NullLocation::getByte() const -> const uint8_t& { throw std::logic_error("Read on null byte"); }

auto NullLocation::getWord() const -> const uint16_t& { throw std::logic_error("Read on null byte"); }

auto NullLocation::operator=(const uint8_t& rhs) -> NullLocation&
{
  (void)rhs;
  throw std::logic_error("Write on null byte");
}

auto NullLocation::operator=(const uint16_t& rhs) -> NullLocation&
{
  (void)rhs;
  throw std::logic_error("Write on null byte");
}
