#ifndef SHIFTROTATEBITWISE_H
#define SHIFTROTATEBITWISE_H

#include <climits>

#include "ops.h"

namespace ops {

namespace detail {

template <typename T> constexpr typename std::make_unsigned<T>::type bitSize()
{
  return sizeof(typename std::make_unsigned<T>::type) * CHAR_BIT;
}

} // namespace detail

template <typename T> OpResult srl(Location<T>& location)
{
  auto result = static_cast<typename std::make_unsigned<T>::type>(location.get()) >> 1;
  location.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <typename T> OpResult rr(Location<T>& location)
{
  auto result = (location.get() >> 1) | (location.get() << (detail::bitSize<T>() - 1));
  location.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <typename T> OpResult rl(Location<T>& location)
{
  auto result = (location.get() << 1) | (location.get() >> (detail::bitSize<T>() - 1));
  location.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

} // namespace ops

#endif // SHIFTROTATEBITWISE_H
