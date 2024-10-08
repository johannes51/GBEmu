#include "logic.h"

#include "location/location.h"

ops::OpResult ops::andF(Location& destination, const Location& source)
{
  const uint8_t result = source.getByte() and destination.getByte();
  destination = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Set, FlagResult::Reset };
}

ops::OpResult ops::orF(Location& destination, const Location& source)
{
  const uint8_t result = source.getByte() or destination.getByte();
  destination = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    FlagResult::Reset };
}

ops::OpResult ops::xorF(Location& destination, const Location& source)
{
  const uint8_t result = source.getByte() xor destination.getByte();
  destination = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    FlagResult::Reset };
}

ops::OpResult ops::cpF(Location& destination, const Location& source)
{
  const auto zero = source.getByte() == destination.getByte();
  const auto carry = source.getByte() < source.getByte();
  const auto halfCarry = (0xF & source.getByte()) < (0xF & source.getByte());
  return { zero ? FlagResult::Set : FlagResult::Reset, FlagResult::Set, halfCarry ? FlagResult::Set : FlagResult::Reset,
    carry ? FlagResult::Set : FlagResult::Reset };
}
