#include "bufferlocation.h"

BufferLocation::BufferLocation(uint8_t& buffer)
    : buffer_(&buffer)
{
}

auto BufferLocation::get() const -> const uint8_t& { return *buffer_; }

auto BufferLocation::operator=(const uint8_t& rhs) -> BufferLocation&
{
  *buffer_ = rhs;
  return *this;
}

void BufferLocation::setBuffer(uint8_t& buffer) { buffer_ = &buffer; }
