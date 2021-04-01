#include "ops.h"

#include "location/location.h"

void ops::add(Location<uint16_t> a, int16_t b) { a.set(a.get() + b); }
