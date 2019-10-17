#ifndef UTIL_DEFINES_H
#define UTIL_DEFINES_H

#include <memory>


template<class T>
class Location;
template<class T>
using LocationUP = std::unique_ptr<Location<T>>;

class LocationByte;
using LocationByteUP = std::unique_ptr<LocationByte>;

#endif // UTIL_DEFINES_H
