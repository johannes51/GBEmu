#include "variablelocation.h"

#include "../common/fusedlocation16.h"
#include "constants.h"

VariableLocation::VariableLocation(const uint8_t& variable)
    : variable_(variable)
{
}

auto VariableLocation::get() const -> const uint8_t& { return variable_; }

void VariableLocation::set(const uint8_t& value) { variable_ = value; }

auto variableLocation(const uint8_t& value) -> Location8 { return { std::make_unique<VariableLocation>(value) }; }

auto variableLocation(const uint8_t& lowValue, const uint8_t& highValue) -> Location16
{
  return { FusedLocation16::construct({variableLocation(lowValue)}, {variableLocation(highValue)}) };
}

auto variableLocation(const uint16_t& value) -> Location16
{
  const uint8_t lower = value & BYTE_MASK;
  const uint8_t upper = static_cast<uint16_t>(value >> BYTE_SHIFT) & BYTE_MASK;
  return variableLocation(lower, upper);
}
