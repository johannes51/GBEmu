#ifndef REGISTERSIMPL_H
#define REGISTERSIMPL_H

#include <vector>

#include "location/location_defines.h"
#include "registersinterface.h"

class CpuRegisters final : public RegistersInterface {
public:
  CpuRegisters();
  ~CpuRegisters();
  DISABLE_COPY_AND_MOVE(CpuRegisters)

  LocationUP<uint16_t> af();
  LocationUP<uint8_t> a();
  LocationUP<uint16_t> bc();
  LocationUP<uint8_t> b();
  LocationUP<uint8_t> c();
  LocationUP<uint16_t> de();
  LocationUP<uint8_t> d();
  LocationUP<uint8_t> e();
  LocationUP<uint16_t> hl();
  LocationUP<uint8_t> h();
  LocationUP<uint8_t> l();
  LocationUP<uint16_t> sp();
  LocationUP<uint16_t> pc();
  FlagsView &getFlags();

private:
  std::vector<uint8_t> registers_;
  FlagsViewUP flags_;
};

#endif // REGISTERSIMPL_H
