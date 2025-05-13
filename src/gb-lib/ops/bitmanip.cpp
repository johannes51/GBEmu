#include "bitmanip.h"

#include "location/location16.h"
#include "location/location8.h"

auto ops::bit(const Location8& location, uint8_t bitPos) -> ops::OpResult
{
  const auto result = (static_cast<unsigned int>(location.get() >> bitPos) & 0b1U) == 0;
  return { .z = result ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Set,
    .c = FlagResult::NoChange };
}

auto ops::bit(const Location16& location, uint8_t bitPos) -> ops::OpResult
{
  const auto result = (static_cast<unsigned int>(location.get() >> bitPos) & 0b1U) == 0;
  return { .z = result ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Set,
    .c = FlagResult::NoChange };
}

auto ops::set(Location8& location, uint8_t bitPos) -> ops::OpResult
{
  const uint8_t result = location.get() | (0b1U << bitPos);
  location = result;
  return {};
}

auto ops::reset(Location8& location, uint8_t bitPos) -> ops::OpResult
{
  const uint8_t result = location.get() & ~(0b1U << bitPos);
  location = result;
  return {};
}
