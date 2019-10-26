#include "variablebyte.h"

VariableByte::VariableByte(uint8_t variable)
    : variable_(variable)
{
}

uint8_t VariableByte::get() const { return variable_; }

void VariableByte::set(const uint8_t& value) { variable_ = value; }
