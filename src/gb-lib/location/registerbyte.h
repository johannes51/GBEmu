#ifndef REGISTERBYTE_H
#define REGISTERBYTE_H

#include "location/locationbyte.h"

class RegisterByte final : public LocationByte {
public:
  RegisterByte(uint8_t &byte);
  DISABLE_COPY_AND_MOVE(RegisterByte)

  uint8_t get() const override;
  void set(const uint8_t &value) override;

private:
  uint8_t &byte_;
};

#endif // REGISTERBYTE_H
