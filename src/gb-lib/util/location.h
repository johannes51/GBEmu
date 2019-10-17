#ifndef LOCATION_H
#define LOCATION_H

#include "util_defines.h"
#include "mem/mem_defines.h"
#include "locationimpl.h"


template<class T>
class Location : LocationImpl
{
public:
  static Location generate(LocationByte&& lower, LocationByte&& upper = NullByte());

  Location(const Location& rhs) = delete;

  T operator *() const;

private:
  Location(LocationByte&& lower, LocationByte&& upper);
};

template<class T>
Location<T> Location<T>::generate(LocationByte&& lower, LocationByte&& upper)
{
  return Location<T>(std::move(lower), std::move(upper));
}



#endif // LOCATION_H
