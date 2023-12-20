#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <cstring>
#include <limits>

#include "ops.h"

namespace ops {

template <typename T> OpResult increment(Location<T>& location)
{
  T result = location.get() + 1;
  location.set(result);
  auto halfCarry = (result & 0xF) != 0;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
    halfCarry ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange };
}

template <typename T> OpResult decrement(Location<T>& location)
{
  T result = location.get() - 1;
  location.set(result);
  auto halfCarry = (result & 0xF) != 0xF;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
    halfCarry ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange };
}

template <typename T> OpResult add(Location<T>& a, const Location<T>& b)
{
  T result = a.get() + b.get();
  a.set(result);
  auto carry = std::numeric_limits<T>::max() - a.get() < b.get();
  auto halfCarry = (0xF & a.get()) + (0xF & b.get()) > 0xF;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset,
    halfCarry ? FlagResult::Set : FlagResult::Reset, carry ? FlagResult::Set : FlagResult::Reset };
}

template <typename T> auto addSigned(Location<T>& a, const Location<uint8_t>& bUnsigned) -> OpResult
{
  auto operandUnsigned = bUnsigned.get();
  int8_t operand = 0;
  std::memcpy(&operand, &operandUnsigned, sizeof(operand)); // NOTE: this only works as 2's complement (so always)
  T result = a.get() + operand;
  a.set(result);

  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::NoChange,
    FlagResult::NoChange };
}

template <typename T> OpResult sub(Location<T>& a, const Location<T>& b)
{
  T result = a.get() - b.get();
  a.set(result);
  auto carry = a.get() < b.get();
  auto halfCarry = (0xF & a.get()) < (0xF & b.get());
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Set,
    halfCarry ? FlagResult::Set : FlagResult::Reset, carry ? FlagResult::Set : FlagResult::Reset };
}

template <typename T> OpResult complement(Location<T>& operand)
{
  operand.set(operand.get() xor 0xFF);
  return { FlagResult::NoChange, FlagResult::Set, FlagResult::Set, FlagResult::NoChange };
}

template <typename T> OpResult decimalAdjust(Location<T>& operand)
{
  (void)operand; // TODO: look up and implement
  auto carry = false;
  return { (operand.get() == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::NoChange, FlagResult::Reset,
    carry ? FlagResult::Set : FlagResult::Reset };
}

} // namespace ops

#endif // ARITHMETIC_H
