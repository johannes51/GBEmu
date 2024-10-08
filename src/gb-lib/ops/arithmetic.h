#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <limits>

#include "location/location.h"
#include "ops.h"

namespace ops {

template <typename T> OpResult increment(Location& location)
{
  T result = location.template get<T>() + 1;
  location = result;
  auto halfCarry = (result & 0xF) != 0;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
    halfCarry ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange };
}

template <typename T> OpResult decrement(Location& location)
{
  T result = location.template get<T>() - 1;
  location = result;
  auto halfCarry = (result & 0xF) != 0xF;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
    halfCarry ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange };
}

template <typename T> OpResult add(Location& a, const Location& b)
{
  T result = a.template get<T>() + b.template get<T>();
  a = result;
  auto carry = std::numeric_limits<T>::max() - a.template get<T>() < b.template get<T>();
  auto halfCarry = (0xF & a.template get<T>()) + (0xF & b.template get<T>()) > 0xF;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
    halfCarry ? FlagResult::Set : FlagResult::Reset, carry ? FlagResult::Set : FlagResult::Reset };
}

auto addSigned(Location& a, const Location& bUnsigned) -> OpResult;

OpResult sub(Location& a, const Location& b);

OpResult complement(Location& operand);

OpResult decimalAdjust(Location& operand);

} // namespace ops

#endif // ARITHMETIC_H
