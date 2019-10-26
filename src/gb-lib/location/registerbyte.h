#ifndef REGISTERBYTE_H
#define REGISTERBYTE_H

#include "location/bufferbyte.h"

class RegisterByte final : public BufferByte {
public:
  RegisterByte(uint8_t& byte);
  DISABLE_COPY_AND_MOVE(RegisterByte)
};

#endif // REGISTERBYTE_H
