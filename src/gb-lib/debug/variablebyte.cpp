#include "variablebyte.h"

VariableByte::VariableByte(uint8_t variable)
    : variable_(variable)
{
}

auto VariableByte::get() const -> uint8_t { return variable_; }

void VariableByte::set(const uint8_t& value) { variable_ = value; }
