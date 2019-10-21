#include "rombyte.h"

#include <stdexcept>

RomByte::RomByte(uint8_t &reference) : BufferByte(reference) {}

void RomByte::set(const uint8_t &value) {
  (void)value;
  throw std::logic_error("Write on ROM");
}
