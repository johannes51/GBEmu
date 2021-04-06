#include "registerbank.h"

#include <stdexcept>

#include "location/location.h"
#include "location/rambyte.h"

RegisterBank::RegisterBank(const address_type& start, const uint8_t& initial)
    : start_(start)
    , buffer_(initial)
{
}

auto RegisterBank::availableAreas() -> std::vector<MemoryArea> { return { { start_, start_ } }; }

auto RegisterBank::getByte(address_type address) -> Location<uint8_t>
{
  if (address != start_) {
    throw std::invalid_argument("Out of bounds");
  }
  return Location<uint8_t>::generate(std::make_unique<RamByte>(buffer_));
}

auto RegisterBank::getWord(address_type address) -> Location<uint16_t>
{
  (void)address;
  throw std::invalid_argument("Out of bounds");
}
