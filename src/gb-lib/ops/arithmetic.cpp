#include "arithmetic.h"

#include "bitmanip.h"
#include "constants.h"

#include <cstring>

auto ops::addSigned(Location& a, const Location& bUnsigned) -> ops::OpResult
{
  auto operandUnsigned = bUnsigned.get<uint8_t>();
  int8_t operand = 0;
  std::memcpy(&operand, &operandUnsigned, sizeof(operand)); // NOTE: this only works as 2's complement (so always)
  const uint16_t result = a.get<uint16_t>() + operand;

  const auto halfCarry = ((bit(a, 3U).z == FlagResult::Set) && (bit(bUnsigned, 3U).z == FlagResult::Reset));
  const auto carry = ((bit(a, 7U).z == FlagResult::Set) && (bit(bUnsigned, 7U).z == FlagResult::Reset));

  a = result;

  return { FlagResult::Reset, FlagResult::Reset, halfCarry ? FlagResult::Set : FlagResult::Reset,
    carry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::sub(Location& a, const Location& b) -> ops::OpResult
{
  auto borrow = a.getByte() < b.getByte();
  auto halfBorrow = (MASK_LOWER_HALF_BYTE & a.getByte()) < (MASK_LOWER_HALF_BYTE & b.getByte());

  const uint8_t result = a.getByte() - b.getByte();
  a = result;

  return { (result == 0U) ? FlagResult::Set : FlagResult::Reset, FlagResult::Set,
    !halfBorrow ? FlagResult::Set : FlagResult::Reset, !borrow ? FlagResult::Set : FlagResult::Reset };
}

auto ops::complement(Location& operand) -> ops::OpResult
{
  operand = static_cast<uint8_t>(operand.getByte() ^ std::numeric_limits<uint8_t>::max());
  return { FlagResult::NoChange, FlagResult::Set, FlagResult::Set, FlagResult::NoChange };
}

auto ops::decimalAdjust(Location& operand) -> ops::OpResult
{
  uint8_t lowerNibble = 0U;
  uint8_t upperNibble = 0U;
  // NOLINTBEGIN(*-magic-numbers)
  switch (operand.getByte() % 10U) {
  case 0:
  default:
    lowerNibble = 0b0000;
    break;
  case 1:
    lowerNibble = 0b0001;
    break;
  case 2:
    lowerNibble = 0b0010;
    break;
  case 3:
    lowerNibble = 0b0011;
    break;
  case 4:
    lowerNibble = 0b0100;
    break;
  case 5:
    lowerNibble = 0b0101;
    break;
  case 6:
    lowerNibble = 0b0110;
    break;
  case 7:
    lowerNibble = 0b0111;
    break;
  case 8:
    lowerNibble = 0b1000;
    break;
  case 9:
    lowerNibble = 0b1001;
    break;
  }
  switch (operand.getByte() / 10U) {
  case 0:
  default:
    upperNibble = 0b0000;
    break;
  case 1:
    upperNibble = 0b0001;
    break;
  case 2:
    upperNibble = 0b0010;
    break;
  case 3:
    upperNibble = 0b0011;
    break;
  case 4:
    upperNibble = 0b0100;
    break;
  case 5:
    upperNibble = 0b0101;
    break;
  case 6:
    upperNibble = 0b0110;
    break;
  case 7:
    upperNibble = 0b0111;
    break;
  case 8:
    upperNibble = 0b1000;
    break;
  case 9:
    upperNibble = 0b1001;
    break;
  }
  // NOLINTEND(*-magic-numbers)
  const auto result = static_cast<uint8_t>(static_cast<uint8_t>(upperNibble << HALF_BYTE_SHIFT) | lowerNibble);

  operand = result;
  return { (operand.getByte() == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange, FlagResult::Reset,
    FlagResult::Reset };
}
