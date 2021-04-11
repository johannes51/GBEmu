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
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <typename T> OpResult decrement(Location<T>& location)
{
  T result = location.get() - 1;
  location.set(result);
  if (result == 0) {
    return { 1, 1, -1, -1 };
  } else {
    return { 0, 1, -1, -1 };
  }
}

template <typename T> OpResult add(Location<T>& a, const Location<T>& b)
{
  T result = a.get() + b.get();
  a.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <typename T> auto addSigned(Location<T>& a, const Location<uint8_t>& bUnsigned) -> OpResult
{
  auto operandUnsigned = bUnsigned.get();
  int8_t operand = 0;
  std::memcpy(&operand, &operandUnsigned, sizeof(operand)); // WARNING: this only works as 2's complement (so always)
  auto result = a.get() + operand;
  a.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <typename T> OpResult sub(Location<T>& a, const Location<T>& b)
{
  T result = a.get() - b.get();
  a.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

} // namespace ops

#endif // ARITHMETIC_H
