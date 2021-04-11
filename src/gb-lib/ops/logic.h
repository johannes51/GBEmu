#ifndef LOGIC_H
#define LOGIC_H

#include "ops.h"

namespace ops {

template <typename T> OpResult andF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() and destination.get();
  destination.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <typename T> OpResult orF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() or destination.get();
  destination.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <typename T> OpResult xorF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() xor destination.get();
  destination.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <typename T> OpResult cpF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() - destination.get();
  if (result == 0) {
    return { 1, 1, -1, result < 0 ? 1 : 0 };
  } else {
    return { 0, 1, -1, result < 0 ? 1 : 0 };
  }
}

} // namespace ops

#endif // LOGIC_H
