#include "registerbyte.h"

RegisterByte::RegisterByte(uint8_t &byte) : byte_(byte) {}

uint8_t RegisterByte::get() const { return byte_; }

void RegisterByte::set(const uint8_t &value) { byte_ = value; }
