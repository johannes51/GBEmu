#ifndef LOCATION_DEFINES_H
#define LOCATION_DEFINES_H

#include <memory>

#include "defines.h"

template <typename T> class Location;

class LocationByte;
using LocationByteUP = std::unique_ptr<LocationByte>;

#endif // LOCATION_DEFINES_H
