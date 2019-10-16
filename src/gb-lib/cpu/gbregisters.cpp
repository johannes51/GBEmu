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

Location<uint16_t>&& GBRegisters::af()
{
  return Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint8_t>&& GBRegisters::a()
{
  return Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint16_t>&& GBRegisters::bc()
{
  return Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint8_t>&& GBRegisters::b()
{
  return Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint8_t>&& GBRegisters::c()
{
  return Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint16_t>&& GBRegisters::de()
{
  return Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint8_t>&& GBRegisters::d()
{
  return Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint8_t>&& GBRegisters::e()
{
  return Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint16_t>&& GBRegisters::hl()
{
  return Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint8_t>&& GBRegisters::h()
{
  return Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint8_t>&& GBRegisters::l()
{
  return Location<uint8_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint16_t>&& GBRegisters::sp()
{
  return Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
}

Location<uint16_t>&& GBRegisters::pc()
{
  return Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
}

FlagsView& GBRegisters::getFlags()
{
  CpuFlags a;
  return a;
}
