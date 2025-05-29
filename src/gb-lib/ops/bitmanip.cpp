#include "bitmanip.h"

#include "mem/ilocation16.h"
#include "mem/ilocation8.h"

auto ops::bit(const ILocation8& location, uint8_t bitPos) -> ops::OpResult
{
  const auto result = (static_cast<unsigned>(location.get() >> bitPos) & 0b1U) == 0;
  return { .z = result ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Set,
    .c = FlagResult::NoChange };
}

auto ops::bit(const ILocation16& location, uint8_t bitPos) -> ops::OpResult
{
  const auto result = (static_cast<unsigned>(location.get() >> bitPos) & 0b1U) == 0;
  return { .z = result ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Set,
    .c = FlagResult::NoChange };
}

auto ops::set(ILocation8& location, uint8_t bitPos) -> ops::OpResult
{
  const uint8_t result = location.get() | (0b1U << bitPos);
  location = result;
  return {};
}

auto ops::reset(ILocation8& location, uint8_t bitPos) -> ops::OpResult
{
  const uint8_t result = location.get() & ~(0b1U << bitPos);
  location = result;
  return {};
}
