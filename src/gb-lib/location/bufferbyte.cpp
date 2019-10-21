#include "bufferbyte.h"

BufferByte::BufferByte(uint8_t &reference) : reference_(reference) {}

uint8_t BufferByte::get() const { return reference_; }

void BufferByte::set(const uint8_t &value) { reference_ = value; }
