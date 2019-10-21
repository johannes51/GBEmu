#include "nullbyte.h"

#include <stdexcept>

uint8_t NullByte::get() const { throw std::logic_error("Read on null byte"); }

void NullByte::set(const uint8_t &value) {
  (void)value;
  throw std::logic_error("Write on null byte");
}
