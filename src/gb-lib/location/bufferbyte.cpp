#include "bufferbyte.h"

BufferByte::BufferByte(uint8_t& reference)
    : reference_(reference)
{
}

auto BufferByte::get() const -> uint8_t { return reference_; }

void BufferByte::set(const uint8_t& value) { reference_ = value; }
