#include "logic.h"

#include "constants.h"
#include "location/location.h"

auto ops::andF(Location& destination, const Location& source) -> ops::OpResult
{
  const uint8_t result = source.getByte() & destination.getByte();
  destination = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Set, FlagResult::Reset };
}

auto ops::orF(Location& destination, const Location& source) -> ops::OpResult
{
  const uint8_t result = source.getByte() | destination.getByte();
  destination = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    FlagResult::Reset };
}

auto ops::xorF(Location& destination, const Location& source) -> ops::OpResult
{
  const uint8_t result = source.getByte() ^ destination.getByte();
  destination = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    FlagResult::Reset };
}

auto ops::cpF(Location& destination, const Location& source) -> ops::OpResult
{
  const auto zero = source.getByte() == destination.getByte();
  const auto carry = source.getByte() < source.getByte();
  const auto halfCarry = (MASK_LOWER_HALF_BYTE & source.getByte()) < (MASK_LOWER_HALF_BYTE & source.getByte());
  return { zero ? FlagResult::Set : FlagResult::Reset, FlagResult::Set, halfCarry ? FlagResult::Set : FlagResult::Reset,
    carry ? FlagResult::Set : FlagResult::Reset };
}
