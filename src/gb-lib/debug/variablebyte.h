#ifndef VARIABLEBYTE_H
#define VARIABLEBYTE_H

#include "location/locationbyte.h"

class VariableByte : public LocationByte {
public:
  VariableByte(uint8_t variable = 0);

  uint8_t operator*();
  VariableByte &operator<<(const uint8_t &value);

private:
  uint8_t variable_;
};

#endif // VARIABLEBYTE_H
