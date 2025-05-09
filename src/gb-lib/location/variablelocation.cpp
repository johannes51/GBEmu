#include "variablelocation.h"

#include "constants.h"
#include "fusedlocation16.h"

VariableLocation::VariableLocation(const uint8_t& variable)
    : Location8()
    , variable_(variable)
{
}

auto VariableLocation::get() const -> const uint8_t& { return variable_; }

auto VariableLocation::operator=(const uint8_t& rhs) -> VariableLocation&
{
  variable_ = rhs;
  return *this;
}

auto variableLocation(const uint8_t& value) -> Location8UP { return std::make_unique<VariableLocation>(value); }

auto variableLocation(const uint8_t& lowValue, const uint8_t& highValue) -> Location16UP
{
  return std::make_unique<FusedLocation16>(variableLocation(lowValue), variableLocation(highValue));
}

auto variableLocation(const uint16_t& value) -> Location16UP
{
  const uint8_t lower = value & BYTE_MASK;
  const uint8_t upper = static_cast<uint16_t>(value >> BYTE_SHIFT) & BYTE_MASK;
  return variableLocation(lower, upper);
}
