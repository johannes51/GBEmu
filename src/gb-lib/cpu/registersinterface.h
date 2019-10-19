#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

#include "cpu_defines.h"
#include "location/location_defines.h"


class RegistersInterface
{
public:
  virtual ~RegistersInterface() = default;

  virtual Location<uint16_t>& af() = 0;
  virtual Location<uint8_t>& a() = 0;
  virtual Location<uint16_t>& bc() = 0;
  virtual Location<uint8_t>& b() = 0;
  virtual Location<uint8_t>& c() = 0;
  virtual Location<uint16_t>& de() = 0;
  virtual Location<uint8_t>& d() = 0;
  virtual Location<uint8_t>& e() = 0;
  virtual Location<uint16_t>& hl() = 0;
  virtual Location<uint8_t>& h() = 0;
  virtual Location<uint8_t>& l() = 0;

  virtual Location<uint16_t>& sp() = 0;
  virtual Location<uint16_t>& pc() = 0;

  virtual FlagsView& getFlags() = 0;

protected:
  RegistersInterface() = default;
};

#endif // REGISTERS_H
