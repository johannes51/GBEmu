#include "logic.h"

#include "constants.h"
#include "location/location8.h"

auto ops::andF(Location8& destination, const Location8& source) -> ops::OpResult
{
  const uint8_t result = source.get() & destination.get();
  destination = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    FlagResult::Reset };
}

auto ops::orF(Location8& destination, const Location8& source) -> ops::OpResult
{
  const uint8_t result = source.get() | destination.get();
  destination = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    FlagResult::Reset };
}

auto ops::xorF(Location8& destination, const Location8& source) -> ops::OpResult
{
  const uint8_t result = source.get() ^ destination.get();
  destination = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    FlagResult::Reset };
}

auto ops::cpF(Location8& destination, const Location8& source) -> ops::OpResult
{
  const auto zero = source.get() == destination.get();
  const auto carry = destination.get() < source.get();
  const auto halfCarry = (MASK_LOWER_HALF_BYTE & destination.get()) < (MASK_LOWER_HALF_BYTE & source.get());
  return { zero ? FlagResult::Set : FlagResult::Reset, FlagResult::Set, halfCarry ? FlagResult::Set : FlagResult::Reset,
    carry ? FlagResult::Set : FlagResult::Reset };
}
