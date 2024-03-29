#ifndef LOCATION_H
#define LOCATION_H

#include "locationimpl.h"
#include "mem/mem_defines.h"
#include "nullbyte.h"

template <typename T> class Location final : LocationImpl {
public:
  static Location<T> generate(LocationByteUP lower, LocationByteUP upper = std::make_unique<NullByte>());
  static Location<uint16_t> fuse(Location<uint8_t> lower, Location<uint8_t> upper);

  Location();
  DISABLE_COPY(Location)
  Location(Location&& rhs) = default;
  Location& operator=(Location&&) = default;

  T get() const;
  void set(const T& value);

private:
  Location(LocationByteUP lower, LocationByteUP upper);
};

template <typename T>
Location<T>::Location()
    : LocationImpl(nullptr, nullptr)
{
}

template <typename T>
Location<T>::Location(LocationByteUP lower, LocationByteUP upper)
    : LocationImpl(std::move(lower), std::move(upper))
{
}

template <typename T> Location<T> Location<T>::generate(LocationByteUP lower, LocationByteUP upper)
{
  return Location<T>(std::move(lower), std::move(upper));
}

#endif // LOCATION_H
