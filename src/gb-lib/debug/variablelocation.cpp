#include "variablelocation.h"


VariableLocation::VariableLocation(uint8_t variable)
  : variable_(variable)
{
}

uint8_t VariableLocation::operator *()
{
  return variable_;
}

VariableLocation& VariableLocation::operator <<(const uint8_t& value)
{
  variable_ = value;
  return *this;
}
