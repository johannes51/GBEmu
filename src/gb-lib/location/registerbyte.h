#ifndef REGISTERBYTE_H
#define REGISTERBYTE_H

#include "location/locationbyte.h"

class RegisterByte : public LocationByte {
public:
  RegisterByte(uint8_t &byte);
  DISABLE_COPY_AND_MOVE(RegisterByte)

  uint8_t operator*();
  RegisterByte &operator<<(const uint8_t &value);

private:
  uint8_t &byte_;
};

#endif // REGISTERBYTE_H
