#include "registerbyte.h"

RegisterByte::RegisterByte(uint8_t &byte) : byte_(byte) {}

uint8_t RegisterByte::operator*() { return byte_; }

RegisterByte &RegisterByte::operator<<(const uint8_t &value) {
  byte_ = value;
  return *this;
}
