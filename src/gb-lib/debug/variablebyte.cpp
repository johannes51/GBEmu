#include "variablebyte.h"

VariableByte::VariableByte(uint8_t variable) : variable_(variable) {}

uint8_t VariableByte::operator*() { return variable_; }

VariableByte &VariableByte::operator<<(const uint8_t &value) {
  variable_ = value;
  return *this;
}
