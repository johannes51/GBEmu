#include "bufferlocation.h"

auto BufferLocation::getByte() const -> const uint8_t& { return area_.getByteReference(start_); }

auto BufferLocation::getWord() const -> const uint16_t&
{
  if (!isWord()) {
    throw std::logic_error("Tried for word value from non-word location");
  }
  return area_.getWordReference(start_);
}

auto BufferLocation::operator=(const uint8_t& rhs) -> BufferLocation&
{
  area_.getByteReference(start_) = rhs;
  return *this;
}

auto BufferLocation::operator=(const uint16_t& rhs) -> BufferLocation&
{
  area_.getWordReference(start_) = rhs;
  return *this;
}

BufferLocation::BufferLocation(Type type, BufferBank& area, address_type start)
    : Location(type)
    , area_(area)
    , start_(start)
{
}
