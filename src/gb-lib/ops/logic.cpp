#include "logic.h"

#include "constants.h"
#include "location/location8.h"

auto ops::andF(Location8& destination, const Location8& source) -> ops::OpResult
{
  const uint8_t result = source.get() & destination.get();
  destination = result;
  return { .z = (result == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Set,
    .c = FlagResult::Reset };
}

auto ops::orF(Location8& destination, const Location8& source) -> ops::OpResult
{
  const uint8_t result = source.get() | destination.get();
  destination = result;
  return { .z = (result == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Reset,
    .c = FlagResult::Reset };
}

auto ops::xorF(Location8& destination, const Location8& source) -> ops::OpResult
{
  const uint8_t result = source.get() ^ destination.get();
  destination = result;
  return { .z = (result == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Reset,
    .c = FlagResult::Reset };
}

auto ops::cpF(Location8& destination, const Location8& source) -> ops::OpResult
{
  const auto zero = source.get() == destination.get();
  const auto carry = destination.get() < source.get();
  const auto halfCarry = (LOWER_HALF_BYTE_MASK & destination.get()) < (LOWER_HALF_BYTE_MASK & source.get());
  return { .z = zero ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Set,
    .h = halfCarry ? FlagResult::Set : FlagResult::Reset,
    .c = carry ? FlagResult::Set : FlagResult::Reset };
}
