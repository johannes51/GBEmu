#ifndef REGISTERBYTE_H
#define REGISTERBYTE_H

#include "util/locationbyte.h"


class RegisterByte : public LocationByte
{
public:
  RegisterByte(uint8_t& byte);

  uint8_t operator *();

private:
  uint8_t& byte_;
};

#endif // REGISTERBYTE_H
