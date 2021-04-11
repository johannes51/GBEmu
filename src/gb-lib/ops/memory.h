#ifndef MEMORY_H
#define MEMORY_H

#include "ops.h"

namespace ops {

template <typename T> void load(Location<T>& destination, const Location<T>& source) { destination.set(source.get()); }

} // namespace ops

#endif // MEMORY_H
