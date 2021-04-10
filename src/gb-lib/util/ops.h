#ifndef OPS_H
#define OPS_H

#include "location/location_defines.h"

namespace ops {

struct OpResult {
  OpResult(int z, int n, int h, int c)
      : z(z)
      , n(n)
      , h(h)
      , c(c)
  {
  }
  int z;
  int n;
  int h;
  int c;
};

template <class T> OpResult increment(Location<T>& location)
{
  T result = location.get() + 1;
  location.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <class T> OpResult decrement(Location<T>& location)
{
  T result = location.get() - 1;
  location.set(result);
  if (result == 0) {
    return { 1, 1, -1, -1 };
  } else {
    return { 0, 1, -1, -1 };
  }
}

template <class T> OpResult add(Location<T>& a, const Location<T>& b)
{
  T result = a.get() + b.get();
  a.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

OpResult add(Location<uint16_t>& a, int16_t b);

template <class T> OpResult sub(Location<T>& a, const Location<T>& b)
{
  T result = a.get() - b.get();
  a.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <class T> void load(Location<T>& destination, const Location<T>& source) { destination.set(source.get()); }

template <class T> OpResult andF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() and destination.get();
  destination.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <class T> OpResult orF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() or destination.get();
  destination.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <class T> OpResult xorF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() xor destination.get();
  destination.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}

template <class T> OpResult cpF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() - destination.get();
  if (result == 0) {
    return { 1, 1, -1, result < 0 ? 1 : 0 };
  } else {
    return { 0, 1, -1, result < 0 ? 1 : 0 };
  }
}

} // namespace ops

#endif // OPS_H
