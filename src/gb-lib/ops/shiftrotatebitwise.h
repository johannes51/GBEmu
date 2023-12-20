#ifndef SHIFTROTATEBITWISE_H
#define SHIFTROTATEBITWISE_H

#include <climits>
#include <cstdint>

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
  T result = static_cast<typename std::make_unsigned<T>::type>(location.get()) >> 1;
  location.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::Reset, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  }
}

template <typename T> OpResult rr(Location<T>& location)
{
  T result = (location.get() >> 1) | (location.get() << (detail::bitSize<T>() - 1));
  location.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::Reset, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  }
}

template <typename T> OpResult rl(Location<T>& location)
{
  T result = (location.get() << 1) | (location.get() >> (detail::bitSize<T>() - 1));
  location.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::Reset, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  }
}

inline OpResult swap(Location<uint8_t>& location)
{
  uint8_t result = ((location.get() & 0x0F) << 4) | ((location.get() & 0xF0) >> 4);
  location.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::Reset, FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange };
  }
}

} // namespace ops

#endif // SHIFTROTATEBITWISE_H
