#ifndef LOGIC_H
#define LOGIC_H

#include "ops.h"

namespace ops {

template <typename T> OpResult andF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() and destination.get();
  destination.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange };
  }
}

template <typename T> OpResult orF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() or destination.get();
  destination.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange };
  }
}

template <typename T> OpResult xorF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() xor destination.get();
  destination.set(result);
  if (result == 0) {
    return { FlagResult::Set, FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange };
  } else {
    return { FlagResult::Reset, FlagResult::NoChange, FlagResult::NoChange, FlagResult::NoChange };
  }
}

template <typename T> OpResult cpF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() - destination.get();
  if (result == 0) {
    return { FlagResult::Set, FlagResult::Set, FlagResult::NoChange, result < 0 ? FlagResult::Set : FlagResult::Reset };
  } else {
    return { FlagResult::Reset, FlagResult::Set, FlagResult::NoChange,
      result < 0 ? FlagResult::Set : FlagResult::Reset };
  }
}

} // namespace ops

#endif // LOGIC_H
