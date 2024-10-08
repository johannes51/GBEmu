#include "bufferlocation.h"

const uint8_t& BufferLocation::getByte() const
{
  return area_.getByteReference(start_);
}

const uint16_t& BufferLocation::getWord() const
{
  return area_.getWordReference(start_);
}

Location& BufferLocation::operator=(const uint8_t& rhs)
{
  area_.getByteReference(start_) = rhs;
  return *this;
}

Location& BufferLocation::operator=(const uint16_t& rhs)
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
