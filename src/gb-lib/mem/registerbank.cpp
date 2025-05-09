#include "registerbank.h"

#include <stdexcept>

#include "location/ramlocation.h"

RegisterBank::RegisterBank(const address_type& start, const uint8_t& initial)
    : BufferBank({ start, start }, { std::addressof(value_), 1 })
    , start_(start)
    , value_(initial)
{
}

auto RegisterBank::getLocation8(const address_type address) -> Location8UP
{
  if (address != start_) {
    throw std::invalid_argument("Out of bounds");
  }
  return std::make_unique<RamLocation>(*this, start_);
}

auto RegisterBank::getLocation16(const address_type address) -> Location16UP
{
  (void)address;
  throw std::invalid_argument("Out of bounds");

  return {};
}

auto RegisterBank::availableAreas() -> std::vector<MemoryArea> { return { { start_, start_ } }; }
