#include "arithmetic.h"

#include "bitmanip.h"
#include "constants.h"

#include <cstring>

auto ops::increment(Location8& location) -> ops::OpResult
{
  const uint8_t numericalResult = location.get() + 1;
  location = numericalResult;
  auto halfCarry = (static_cast<unsigned int>(numericalResult) & MASK_LOWER_HALF_BYTE) == 0x0U;
  return { (numericalResult == 0x0U) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
    halfCarry ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange };
}

auto ops::increment(Location16& location) -> ops::OpResult
{
  const uint16_t numericalResult = location.get() + 1;
  location = numericalResult;
  return { FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange };
}

auto ops::decrement(Location8& location) -> ops::OpResult
{
  const uint8_t numericalResult = location.get() - 1;
  location = numericalResult;
  auto halfCarry = (numericalResult & MASK_LOWER_HALF_BYTE) != 0;
  return { (numericalResult == 0x0U) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
    halfCarry ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange };
}

auto ops::decrement(Location16& location) -> ops::OpResult
{
  const uint16_t numericalResult = location.get() - 1;
  location = numericalResult;
  return { FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange };
}

auto ops::add(Location8& a, const Location8& b) -> ops::OpResult
{
  auto aVal = a.get();
  auto bVal = b.get();

  auto carry = std::numeric_limits<uint8_t>::max() - aVal < bVal;

  const uint8_t numericalResult = aVal + bVal;
  a = numericalResult;

  auto halfCarry = (MASK_LOWER_HALF_BYTE & aVal) + (MASK_LOWER_HALF_BYTE & bVal) > MASK_LOWER_HALF_BYTE;

  return { (numericalResult == 0x0U) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
    halfCarry ? FlagResult::Set : FlagResult::Reset, carry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::add(Location16& a, const Location16& b) -> ops::OpResult
{
  auto aVal = a.get();
  auto bVal = b.get();

  auto carry = std::numeric_limits<uint16_t>::max() - aVal < bVal;

  const uint16_t numericalResult = aVal + bVal;
  a = numericalResult;

  aVal >>= BYTE_SHIFT;
  bVal >>= BYTE_SHIFT;

  const auto halfCarry = (MASK_LOWER_HALF_BYTE & aVal) + (MASK_LOWER_HALF_BYTE & bVal) > MASK_LOWER_HALF_BYTE;

  return { FlagResult::NoChange, FlagResult::Reset, halfCarry ? FlagResult::Set : FlagResult::Reset,
    carry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::addSigned(Location16& a, const Location8& bUnsigned) -> ops::OpResult
{
  auto operandUnsigned = bUnsigned.get();
  int8_t operand = 0;
  std::memcpy(&operand, &operandUnsigned, sizeof(operand)); // NOTE: this only works as 2's complement (so always)
  const uint16_t result = a.get() + operand;

  const auto halfCarry = ((bit(a, 3U).z == FlagResult::Set) && (bit(bUnsigned, 3U).z == FlagResult::Reset));
  const auto carry = ((bit(a, 7U).z == FlagResult::Set) && (bit(bUnsigned, 7U).z == FlagResult::Reset));

  a = result;

  return { FlagResult::Reset, FlagResult::Reset, halfCarry ? FlagResult::Set : FlagResult::Reset,
    carry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::sub(Location8& a, const Location8& b) -> ops::OpResult
{
  auto borrow = a.get() < b.get();
  auto halfBorrow = (MASK_LOWER_HALF_BYTE & a.get()) < (MASK_LOWER_HALF_BYTE & b.get());

  const uint8_t result = a.get() - b.get();
  a = result;

  return { (result == 0U) ? FlagResult::Set : FlagResult::Reset, FlagResult::Set,
    !halfBorrow ? FlagResult::Set : FlagResult::Reset, !borrow ? FlagResult::Set : FlagResult::Reset };
}

auto ops::complement(Location8& operand) -> ops::OpResult
{
  operand = static_cast<uint8_t>(operand.get() ^ std::numeric_limits<uint8_t>::max());
  return { FlagResult::NoChange, FlagResult::Set, FlagResult::Set, FlagResult::NoChange };
}

auto ops::decimalAdjust(Location8& operand) -> ops::OpResult
{
  uint8_t lowerNibble = 0U;
  uint8_t upperNibble = 0U;
  // NOLINTBEGIN(*-magic-numbers)
  switch (operand.get() % 10U) {
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
  switch (operand.get() / 10U) {
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
  return { (operand.get() == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange, FlagResult::Reset,
    FlagResult::Reset };
}
