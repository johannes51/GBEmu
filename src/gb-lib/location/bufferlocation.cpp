#include "bufferlocation.h"

auto BufferLocation::get() const -> const uint8_t& { return area_.getByteReference(start_); }

auto BufferLocation::operator=(const uint8_t& rhs) -> BufferLocation&
{
  area_.getByteReference(start_) = rhs;
  return *this;
}

BufferLocation::BufferLocation(BufferBank& area, address_type start)
    : Location8()
    , area_(area)
    , start_(start)
{
}
