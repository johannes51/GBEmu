#ifndef LOCATION_H
#define LOCATION_H

#include "mem/mem_defines.h"
#include "locationimpl.h"
#include "nullbyte.h"


template<class T>
class Location : LocationImpl
{
public:
  static LocationUP<T> generate(LocationByteUP lower, LocationByteUP upper = std::make_unique<NullByte>());

  Location(const Location& rhs) = delete;
  Location(Location&& rhs) = default;

  T operator *() const;
  Location<T>& operator <<(const T& value);

private:
  Location(LocationByteUP lower, LocationByteUP upper);
};

template<class T>
Location<T>::Location(LocationByteUP lower, LocationByteUP upper)
  : LocationImpl(std::move(lower), std::move(upper))
{
}

template<class T>
LocationUP<T> Location<T>::generate(LocationByteUP lower, LocationByteUP upper)
{
  return std::unique_ptr<Location<T>>(new Location<T>(std::move(lower), std::move(upper)));
}



#endif // LOCATION_H