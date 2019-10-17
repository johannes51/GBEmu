#ifndef REGISTERSIMPL_H
#define REGISTERSIMPL_H

#include "registersinterface.h"

#include <map>

#include "register_flags.h"
#include "util/util_defines.h"



class CpuRegisters : public RegistersInterface
{
public:
  CpuRegisters();
  virtual ~CpuRegisters();

  Location<uint16_t>& af();
  Location<uint8_t>& a();
  Location<uint16_t>& bc();
  Location<uint8_t>& b();
  Location<uint8_t>& c();
  Location<uint16_t>& de();
  Location<uint8_t>& d();
  Location<uint8_t>& e();
  Location<uint16_t>& hl();
  Location<uint8_t>& h();
  Location<uint8_t>& l();
  Location<uint16_t>& sp();
  Location<uint16_t>& pc();
  FlagsView& getFlags();

private:
  std::map<RegisterFlags, uint8_t> registers_;
  LocationUP<uint16_t> af_;
  LocationUP<uint8_t> a_;
  LocationUP<uint16_t> bc_;
  LocationUP<uint8_t> b_;
  LocationUP<uint8_t> c_;
  LocationUP<uint16_t> de_;
  LocationUP<uint8_t> d_;
  LocationUP<uint8_t> e_;
  LocationUP<uint16_t> hl_;
  LocationUP<uint8_t> h_;
  LocationUP<uint8_t> l_;
  LocationUP<uint16_t> sp_;
  LocationUP<uint16_t> pc_;
  FlagsViewUP flags_;
};

#endif // REGISTERSIMPL_H
