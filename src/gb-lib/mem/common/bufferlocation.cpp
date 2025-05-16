#include "bufferlocation.h"

BufferLocation::BufferLocation(uint8_t& buffer)
    : buffer_(buffer)
{
}

auto BufferLocation::get() const -> const uint8_t& { return buffer_; }

void BufferLocation::set(const uint8_t& value) { buffer_ = value; }
