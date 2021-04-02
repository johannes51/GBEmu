#include "ops.h"

#include "location/location.h"

auto ops::add(Location<uint16_t>& a, int16_t b) -> OpResult
{
  auto result = a.get() + b;
  a.set(result);
  if (result == 0) {
    return { 1, 0, -1, -1 };
  } else {
    return { 0, 0, -1, -1 };
  }
}
