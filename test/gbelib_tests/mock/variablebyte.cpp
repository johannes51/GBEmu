#include "variablebyte.h"

#include "location/location.h"

VariableByte::VariableByte(const uint8_t& variable)
    : variable_(variable)
{
}

auto VariableByte::get() const -> uint8_t { return variable_; }

void VariableByte::set(const uint8_t& value) { variable_ = value; }

auto variableLocation(const uint8_t& value) -> Location<uint8_t>
{
  return Location<uint8_t>::generate(std::make_unique<VariableByte>(value));
}

auto variableLocation(const uint8_t& lowValue, const uint8_t& highValue) -> Location<uint16_t>
{
  return Location<uint16_t>::generate(
      std::make_unique<VariableByte>(lowValue), std::make_unique<VariableByte>(highValue));
}
