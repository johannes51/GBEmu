#ifndef REGISTERSIMPL_H
#define REGISTERSIMPL_H

#include "registersinterface.h"

#include <vector>

#include "register_flags.h"
#include "location/location_defines.h"



class CpuRegisters : public RegistersInterface
{
public:
  CpuRegisters();
  virtual ~CpuRegisters();

  CpuRegisters(const CpuRegisters&) = delete;
  CpuRegisters& operator =(const CpuRegisters&) = delete;

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
  FlagsView& getFlags();

private:
  std::vector<uint8_t> registers_;
  FlagsViewUP flags_;
};

#endif // REGISTERSIMPL_H
