#include "gbregisters.h"

#include "cpuflags.h"
#include "util/location.h"

#include "debug/simplelocation.h"


GBRegisters::GBRegisters()
{
  registers_[RegisterFlags::AF] = 0;
  registers_[RegisterFlags::BC] = 0;
  registers_[RegisterFlags::DE] = 0;
  registers_[RegisterFlags::HL] = 0;
  registers_[RegisterFlags::SP] = 0;
  registers_[RegisterFlags::PC] = 0;
}

Location<uint16_t>& GBRegisters::af()
{
  auto a = Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint8_t>& GBRegisters::a()
{
  auto a = Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint16_t>& GBRegisters::bc()
{
  auto a = Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint8_t>& GBRegisters::b()
{
  auto a = Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint8_t>& GBRegisters::c()
{
  auto a = Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint16_t>& GBRegisters::de()
{
  auto a = Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint8_t>& GBRegisters::d()
{
  auto a = Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint8_t>& GBRegisters::e()
{
  auto a = Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint16_t>& GBRegisters::hl()
{
  auto a = Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint8_t>& GBRegisters::h()
{
  auto a = Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint8_t>& GBRegisters::l()
{
  auto a = Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint16_t>& GBRegisters::sp()
{
  auto a = Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

Location<uint16_t>& GBRegisters::pc()
{
  auto a = Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
  return a;
}

FlagsView& GBRegisters::getFlags()
{
  CpuFlags a;
  return a;
}
