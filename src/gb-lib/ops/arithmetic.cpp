#include "arithmetic.h"

#include <cstring>

auto ops::addSigned(Location& a, const Location& bUnsigned) -> ops::OpResult
{
  auto operandUnsigned = bUnsigned.get<uint8_t>();
  int8_t operand = 0;
  std::memcpy(&operand, &operandUnsigned, sizeof(operand)); // NOTE: this only works as 2's complement (so always)
  uint16_t result = a.get<uint16_t>() + operand;
  a = result;

  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::NoChange,
    FlagResult::NoChange };
}

auto ops::sub(Location& a, const Location& b) -> ops::OpResult
{
  const uint8_t result = a.getByte() - b.getByte();
  a = result;
  auto carry = a.getByte() < b.getByte();
  auto halfCarry = (0xF & a.getByte()) < (0xF & b.getByte());
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Set,
    halfCarry ? FlagResult::Set : FlagResult::Reset, carry ? FlagResult::Set : FlagResult::Reset };
}

ops::OpResult ops::complement(Location& operand)
{
  operand = static_cast<uint8_t>(operand.getByte() xor std::numeric_limits<uint8_t>::max());
  return { FlagResult::NoChange, FlagResult::Set, FlagResult::Set, FlagResult::NoChange };
}

ops::OpResult ops::decimalAdjust(Location& operand)
{
  (void)operand; // TODO: fake! look up and implement
  auto carry = false;
  return { (operand.getByte() == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange, FlagResult::Reset,
    carry ? FlagResult::Set : FlagResult::Reset };
}
