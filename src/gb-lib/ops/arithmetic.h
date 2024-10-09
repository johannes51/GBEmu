#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <limits>

#include "constants.h"
#include "location/location.h"
#include "ops.h"

namespace ops {

template <typename T> OpResult increment(Location& location)
{
  T result = location.template get<T>() + 1;
  location = result;
  if constexpr (sizeof(T) == 1) {
    auto halfCarry = (static_cast<unsigned int>(result) & MASK_LOWER_HALF_BYTE) == 0x0U;
    return { (result == 0x0U) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
      halfCarry ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange };
  } else {
    return { FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange };
  }
}

template <typename T> OpResult decrement(Location& location)
{
  T result = location.template get<T>() - 1;
  location = result;
  if constexpr (sizeof(T) == 1) {
    auto halfCarry = (result & MASK_LOWER_HALF_BYTE) != 0;
    return { (result == 0x0U) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
      halfCarry ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange };
  } else {
    return { FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange };
  }
}

template <typename T> OpResult add(Location& a, const Location& b)
{
  T aVal = a.template get<T>();
  T bVal = b.template get<T>();

  auto carry = std::numeric_limits<T>::max() - aVal < bVal;

  T result = aVal + bVal;
  a = result;

  if constexpr (sizeof(T) > 1) {
    aVal >>= BYTE_SHIFT;
    bVal >>= BYTE_SHIFT;
  }
  auto halfCarry = (MASK_LOWER_HALF_BYTE & aVal) + (MASK_LOWER_HALF_BYTE & bVal) > 0xFU;

  if constexpr (sizeof(T) == 1) {
    return { (result == 0x0U) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
      halfCarry ? FlagResult::Set : FlagResult::Reset, carry ? FlagResult::Set : FlagResult::Reset };
  } else {
    return { FlagResult::NoChange, FlagResult::Reset, halfCarry ? FlagResult::Set : FlagResult::Reset,
      carry ? FlagResult::Set : FlagResult::Reset };
  }
}

auto addSigned(Location& a, const Location& bUnsigned) -> OpResult;

OpResult sub(Location& a, const Location& b);

OpResult complement(Location& operand);

OpResult decimalAdjust(Location& operand);

} // namespace ops

#endif // ARITHMETIC_H
