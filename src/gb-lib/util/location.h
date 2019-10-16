#ifndef LOCATION_H
#define LOCATION_H

#include "util_defines.h"
#include "mem/mem_defines.h"
#include "locationimpl.h"


template<class T>
class Location
{
public:
  static Location&& generate(LocationByte&& lower, LocationByte&& upper);

  Location(const Location& rhs) = delete;

  T operator *() const;

private:
  Location(LocationImpl&& location);

  LocationImpl location_;
};

template<class T>
Location<T>&& Location<T>::generate(LocationByte&& lower, LocationByte&& upper)
{
  return Location<T>(LocationImpl(std::move(lower), std::move(upper)));
}

template<class T>
Location<T>::Location(LocationImpl&& location)
  : location_(location)
{
}

#endif // LOCATION_H
