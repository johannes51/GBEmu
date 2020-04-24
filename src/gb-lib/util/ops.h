#ifndef OPS_H
#define OPS_H

#include "location/location_defines.h"

namespace ops {

template <class T> void increment(Location<T> location) { location.set(location.get() + 1); }
template <class T> void decrement(Location<T> location) { location.set(location.get() - 1); }
template <class T> void add(Location<T> a, const Location<T> b) { a.set(a.get() + b.get()); }
template <class T> void load(Location<T> destination, const Location<T> source) { destination.set(source.get()); }
template <class T> void xorF(Location<T> destination, const Location<T> source)
{
  destination.set(source.get() xor destination.get());
}

} // namespace ops

#endif // OPS_H
