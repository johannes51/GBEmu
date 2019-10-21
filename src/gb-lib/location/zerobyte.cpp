#include "zerobyte.h"

uint8_t ZeroByte::get() const { return 0; }

void ZeroByte::set(const uint8_t &value) {
  (void)value;
}
