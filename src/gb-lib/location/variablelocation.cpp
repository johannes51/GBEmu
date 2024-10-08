#include "variablelocation.h"

#include "constants.h"
#include "location/location.h"

auto variableLocation(const uint8_t& value) -> LocationUP { return std::make_unique<VariableLocation<uint8_t>>(value); }

auto variableLocation(const uint8_t& lowValue, const uint8_t& highValue) -> LocationUP
{
  return std::make_unique<VariableLocation<uint16_t>>(static_cast<unsigned int>(highValue) << BYTE_SHIFT | lowValue);
}

auto variableLocation(const uint16_t& value) -> LocationUP
{
  return std::make_unique<VariableLocation<uint16_t>>(value);
}
