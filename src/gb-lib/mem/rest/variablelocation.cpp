#include "variablelocation.h"

#include "../common/fusedlocation16.h"
#include "constants.h"

VariableLocation8::VariableLocation8(const uint8_t& variable)
    : variable_(variable)
{
}

VariableLocation8::VariableLocation8(VariableLocation8&& other) noexcept
    : variable_(other.variable_)
{
}

auto VariableLocation8::get() const -> const uint8_t& { return variable_; }

auto VariableLocation8::operator=(const uint8_t& rhs) -> VariableLocation8&
{
  variable_ = rhs;
  return *this;
}

VariableLocation16::VariableLocation16(const uint16_t& variable)
    : variable_(variable)
{
}

VariableLocation16::VariableLocation16(VariableLocation16&& other) noexcept
    : variable_(other.variable_)
{
}

auto VariableLocation16::get() const -> const uint16_t& { return variable_; }

auto VariableLocation16::operator=(const uint16_t& rhs) -> VariableLocation16&
{
  variable_ = rhs;
  return *this;
}

auto variableLocation(const uint8_t& value) -> VariableLocation8 { return VariableLocation8 { value }; }

auto variableLocation(const uint8_t& lowValue, const uint8_t& highValue) -> VariableLocation16
{
  const uint16_t value = static_cast<uint16_t>(highValue << BYTE_SHIFT) | lowValue;
  return variableLocation(value);
}

auto variableLocation(const uint16_t& value) -> VariableLocation16 { return VariableLocation16 { value }; }
