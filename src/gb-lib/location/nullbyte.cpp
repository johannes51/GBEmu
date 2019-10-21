#include "nullbyte.h"

#include <stdexcept>

uint8_t NullByte::operator*() { throw std::logic_error("Read on null byte"); }

NullByte &NullByte::operator<<(const uint8_t &value) {
  throw std::logic_error("Write on null byte");
  return *this;
}
