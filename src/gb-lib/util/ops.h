#ifndef OPS_H
#define OPS_H

#include "location/location_defines.h"

namespace ops {

template <class T> void increment(LocationUP<T> location) {
  location->set(location->get() + 1);
}

} // namespace ops

#endif // OPS_H
