#ifndef LOCATION_H
#define LOCATION_H

#include "locationimpl.h"
#include "mem/mem_defines.h"
#include "nullbyte.h"

template <class T> class Location final : LocationImpl {
public:
  static Location<T>
  generate(LocationByteUP lower,
           LocationByteUP upper = std::make_unique<NullByte>());

  Location();
  DISABLE_COPY(Location)
  Location(Location &&rhs) = default;
  Location &operator=(Location &&) = default;

  T get() const;
  void set(const T &value);

private:
  Location(LocationByteUP lower, LocationByteUP upper);
};

template <class T>
Location<T>::Location(LocationByteUP lower, LocationByteUP upper)
    : LocationImpl(std::move(lower), std::move(upper)) {}

template <class T>
Location<T> Location<T>::generate(LocationByteUP lower, LocationByteUP upper) {
  return Location<T>(std::move(lower), std::move(upper));
}

template <class T>
Location<T>::Location() : LocationImpl(LocationByteUP(), LocationByteUP()) {}

#endif // LOCATION_H
