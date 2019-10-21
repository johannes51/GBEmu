#ifndef LOCATION_DEFINES_H
#define LOCATION_DEFINES_H

#include <memory>

#include "defines.h"


template<class T>
class Location;
template<class T>
using LocationUP = std::unique_ptr<Location<T>>;

class LocationByte;
using LocationByteUP = std::unique_ptr<LocationByte>;

#endif // LOCATION_DEFINES_H
