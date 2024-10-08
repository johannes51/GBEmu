#include "bitmanip.h"

#include "location/location.h"

auto ops::bit(Location& location, uint8_t bitPos) -> ops::OpResult
{
  const auto result = (static_cast<unsigned int>(location.getByte() >> bitPos) & 0b1U) == 0;
  return { result ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Set, FlagResult::NoChange };
}

auto ops::set(Location& location, uint8_t bitPos) -> ops::OpResult
{
  const uint8_t result = location.getByte() | (0b1U << bitPos);
  location = result;
  return {};
}

auto ops::reset(Location& location, uint8_t bitPos) -> ops::OpResult
{
  const uint8_t result = location.getByte() & ~(0b1U << bitPos);
  location = result;
  return {};
}
