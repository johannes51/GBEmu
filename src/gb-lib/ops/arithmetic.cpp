#include "arithmetic.h"

#include "bitmanip.h"
#include "constants.h"
#include "mem/rest/variablelocation.h"

#include <cstring>

auto ops::increment(Location8& location) -> ops::OpResult
{
  const uint8_t numericalResult = location.get() + 1;
  location = numericalResult;
  const auto halfCarry = (static_cast<unsigned int>(numericalResult) & LOWER_HALF_BYTE_MASK) == 0x0U;
  return { .z = (numericalResult == 0x0U) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = halfCarry ? FlagResult::Set : FlagResult::Reset,
    .c = FlagResult::NoChange };
}

auto ops::increment(Location16& location) -> ops::OpResult
{
  const uint16_t numericalResult = location.get() + 1;
  location = numericalResult;
  return { .z = FlagResult::NoChange, .n = FlagResult::NoChange, .h = FlagResult::NoChange, .c = FlagResult::NoChange };
}

auto ops::decrement(Location8& location) -> ops::OpResult
{
  const uint8_t numericalResult = location.get() - 1;
  location = numericalResult;
  const auto halfCarry = (numericalResult & LOWER_HALF_BYTE_MASK) == 0xFU;
  return { .z = (numericalResult == 0x0U) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Set,
    .h = halfCarry ? FlagResult::Set : FlagResult::Reset,
    .c = FlagResult::NoChange };
}

auto ops::decrement(Location16& location) -> ops::OpResult
{
  const uint16_t numericalResult = location.get() - 1;
  location = numericalResult;
  return { .z = FlagResult::NoChange, .n = FlagResult::NoChange, .h = FlagResult::NoChange, .c = FlagResult::NoChange };
}

auto ops::add(Location8& a, const Location8& b) -> ops::OpResult
{
  auto aVal = a.get();
  auto bVal = b.get();

  const auto carry = std::numeric_limits<uint8_t>::max() - aVal < bVal;

  const uint8_t numericalResult = aVal + bVal;
  a = numericalResult;

  const auto halfCarry = (LOWER_HALF_BYTE_MASK & aVal) + (LOWER_HALF_BYTE_MASK & bVal) > LOWER_HALF_BYTE_MASK;

  return { .z = (numericalResult == 0x0U) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = halfCarry ? FlagResult::Set : FlagResult::Reset,
    .c = carry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::add_carry(Location8& a, const Location8& b, const bool carryFlag) -> ops::OpResult
{
  const auto aVal = a.get();
  const auto bVal = b.get();

  auto carry = std::numeric_limits<uint8_t>::max() - aVal < bVal;
  auto halfCarry = (LOWER_HALF_BYTE_MASK & aVal) + (LOWER_HALF_BYTE_MASK & bVal) > LOWER_HALF_BYTE_MASK;

  uint8_t numericalResult = aVal + bVal;

  if (carryFlag) {
    carry |= numericalResult == std::numeric_limits<uint8_t>::max();
    halfCarry |= (LOWER_HALF_BYTE_MASK & numericalResult) == LOWER_HALF_BYTE_MASK;
    ++numericalResult;
  }

  a = numericalResult;

  return { .z = (numericalResult == 0x0U) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = halfCarry ? FlagResult::Set : FlagResult::Reset,
    .c = carry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::add(Location16& a, const Location16& b) -> ops::OpResult
{
  const auto aVal = a.get();
  const auto bVal = b.get();

  const uint16_t numericalResult = aVal + bVal;
  a = numericalResult;

  const auto carry = (BIT_15_MASK & aVal) + (BIT_15_MASK & bVal) > BIT_15_MASK;
  const auto halfCarry = (BIT_11_MASK & aVal) + (BIT_11_MASK & bVal) > BIT_11_MASK;

  return { .z = FlagResult::NoChange,
    .n = FlagResult::Reset,
    .h = halfCarry ? FlagResult::Set : FlagResult::Reset,
    .c = carry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::addSigned(Location16& a, const uint8_t bUnsigned) -> ops::OpResult
{
  int8_t operand = 0;
  std::memcpy(&operand, &bUnsigned, sizeof(operand)); // NOTE: this only works as 2's complement (so always)
  const uint16_t aVal = a.get();
  const uint16_t result = aVal + operand;

  const auto halfCarry = (LOWER_HALF_BYTE_MASK & aVal) + (LOWER_HALF_BYTE_MASK & bUnsigned) > LOWER_HALF_BYTE_MASK;
  const auto carry = std::numeric_limits<uint8_t>::max() - (LOWER_BYTE_MASK & aVal) < bUnsigned;

  a = result;

  return { .z = FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = halfCarry ? FlagResult::Set : FlagResult::Reset,
    .c = carry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::sub(Location8& a, const Location8& b) -> ops::OpResult
{
  auto borrow = a.get() < b.get();
  auto halfBorrow = (LOWER_HALF_BYTE_MASK & a.get()) < (LOWER_HALF_BYTE_MASK & b.get());

  const uint8_t result = a.get() - b.get();
  a = result;

  return { .z = (result == 0U) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Set,
    .h = halfBorrow ? FlagResult::Set : FlagResult::Reset,
    .c = borrow ? FlagResult::Set : FlagResult::Reset };
}

auto ops::sub_carry(Location8& a, const Location8& b, const bool carryFlag) -> ops::OpResult
{
  auto borrow = a.get() < b.get();
  auto halfBorrow = (LOWER_HALF_BYTE_MASK & a.get()) < (LOWER_HALF_BYTE_MASK & b.get());

  uint8_t numericalResult = a.get() - b.get();

  if (carryFlag) {
    borrow |= numericalResult == 0U;
    halfBorrow |= (LOWER_HALF_BYTE_MASK & numericalResult) == 0U;
    --numericalResult;
  }

  a = numericalResult;

  return { .z = (numericalResult == 0U) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Set,
    .h = halfBorrow ? FlagResult::Set : FlagResult::Reset,
    .c = borrow ? FlagResult::Set : FlagResult::Reset };
}

auto ops::complement(Location8& operand) -> ops::OpResult
{
  operand = static_cast<uint8_t>(operand.get() ^ std::numeric_limits<uint8_t>::max());
  return { .z = FlagResult::NoChange, .n = FlagResult::Set, .h = FlagResult::Set, .c = FlagResult::NoChange };
}

auto ops::decimalAdjust(
    Location8& operand, const bool carry, const bool halfCarry, const bool subtract) -> ops::OpResult
{
  const auto value = operand.get();

  auto newCarry = carry;
  // NOLINTBEGIN(*-magic-numbers)
  uint8_t offset = 0U;
  if (carry || (!subtract && (value > 0x99U))) {
    offset |= 0x60U;
    newCarry = true;
  }
  if (halfCarry || (!subtract && ((value & 0xFU) > 0x9U))) {
    offset |= 0x6U;
  }
  const auto newValue = static_cast<uint8_t>(subtract ? value - offset : value + offset);
  // NOLINTEND(*-magic-numbers)

  operand = newValue;

  return { .z = (newValue == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::NoChange,
    .h = FlagResult::Reset,
    .c = newCarry ? FlagResult::Set : FlagResult::Reset };
}
