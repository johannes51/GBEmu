#include "registerbank.h"

#include <stdexcept>

#include "location/ramlocation.h"

RegisterBank::RegisterBank(const address_type& start, const uint8_t& initial)
    : BufferBank({start, start}, {std::addressof(value_), 1})
    , start_(start)
    , value_(initial)
{
}

auto RegisterBank::getLocation(const address_type address, bool tryWord) -> LocationUP
{
  if (address != start_ || tryWord) {
    throw std::invalid_argument("Out of bounds");
  }
  return std::make_unique<RamLocation>(Location::Type::Single, *this, start_);
}

auto RegisterBank::availableAreas() -> std::vector<MemoryArea> { return { { start_, start_ } }; }
