#ifndef MEMORY_H
#define MEMORY_H

#include "location/location.h"

namespace ops {

template <typename T> void load(Location& destination, const Location& source)
{
  destination = source.template get<T>();
}

} // namespace ops

#endif // MEMORY_H
