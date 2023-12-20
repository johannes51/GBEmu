#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <cstring>

#include "ops.h"

namespace ops {

template <typename T> OpResult increment(Location<T>& location)
{
  T result = location.get() + 1;
  location.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::Reset, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  }
}

template <typename T> OpResult decrement(Location<T>& location)
{
  T result = location.get() - 1;
  location.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::Set, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::Reset, FlagResult::Set, FlagResult::NoChange, FlagResult::NoChange };
  }
}

template <typename T> OpResult add(Location<T>& a, const Location<T>& b)
{
  T result = a.get() + b.get();
  a.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::Reset, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  }
}

template <typename T> auto addSigned(Location<T>& a, const Location<uint8_t>& bUnsigned) -> OpResult
{
  auto operandUnsigned = bUnsigned.get();
  int8_t operand = 0;
  std::memcpy(&operand, &operandUnsigned, sizeof(operand)); // NOTE: this only works as 2's complement (so always)
  T result = a.get() + operand;
  a.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::Reset, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  }
}

template <typename T> OpResult sub(Location<T>& a, const Location<T>& b)
{
  T result = a.get() - b.get();
  a.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::Reset, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  }
}

} // namespace ops

#endif // ARITHMETIC_H
