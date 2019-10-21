#include "simplelocation.h"

uint8_t SimpleLocation::operator*() { return 0; }

SimpleLocation &SimpleLocation::operator<<(const uint8_t &value) {
  (void)value;
  return *this;
}
