#include "zerobyte.h"

uint8_t ZeroByte::operator*() { return 0; }

LocationByte &ZeroByte::operator<<(const uint8_t &value) {
  (void)value;
  return *this;
}
