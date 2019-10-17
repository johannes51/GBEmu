#include "variablelocation.h"


VariableLocation::VariableLocation(uint8_t variable)
  : variable_(variable)
{
}

uint8_t VariableLocation::operator *()
{
  return variable_;
}
