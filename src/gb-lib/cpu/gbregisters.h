#ifndef REGISTERSIMPL_H
#define REGISTERSIMPL_H

#include "registersinterface.h"

#include <map>

#include "register_flags.h"


class GBRegisters : public RegistersInterface
{
public:
  GBRegisters();

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
  std::map<RegisterFlags, uint16_t> registers_;
};

#endif // REGISTERSIMPL_H
