#ifndef VARIABLELOCATION_H
#define VARIABLELOCATION_H

#include "util/locationbyte.h"


class VariableLocation : public LocationByte
{
public:
  VariableLocation(uint8_t variable = 0);

  uint8_t operator *();

private:
  uint8_t variable_;
};

#endif // VARIABLELOCATION_H
