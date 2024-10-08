#include "bitmanip.h"

#include "location/location.h"

ops::OpResult ops::bit(Location& location, uint8_t bitPos)
{
  const auto result = ((location.getByte() >> bitPos) & 0b1) == 0;
  return { result ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Set, FlagResult::NoChange };
}

ops::OpResult ops::set(Location& location, uint8_t bitPos)
{
  const uint8_t result = location.getByte() | (0b1 << bitPos);
  location = result;
  return {};
}

ops::OpResult ops::reset(Location& location, uint8_t bitPos)
{
  const uint8_t result = location.getByte() & ~(0b1 << bitPos);
  location = result;
  return {};
}
