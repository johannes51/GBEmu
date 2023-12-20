#ifndef LOGIC_H
#define LOGIC_H

#include "ops.h"

namespace ops {

template <typename T> OpResult andF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() and destination.get();
  destination.set(result);
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Set, FlagResult::Reset };
}

template <typename T> OpResult orF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() or destination.get();
  destination.set(result);
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    FlagResult::Reset };
}

template <typename T> OpResult xorF(Location<T>& destination, const Location<T>& source)
{
  T result = source.get() xor destination.get();
  destination.set(result);
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    FlagResult::Reset };
}

template <typename T> OpResult cpF(Location<T>& destination, const Location<T>& source)
{
  auto zero = source.get() == destination.get();
  auto carry = source.get() < source.get();
  auto halfCarry = (0xF & source.get()) < (0xF & source.get());
  return { zero ? FlagResult::Set : FlagResult::Reset, FlagResult::Set, halfCarry ? FlagResult::Set : FlagResult::Reset,
    carry ? FlagResult::Set : FlagResult::Reset };
}

} // namespace ops

#endif // LOGIC_H
