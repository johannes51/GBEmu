#include "cpuregisters.h"

#include "cpuflags.h"
#include "location/location.h"
#include "location/registerbyte.h"

#include "debug/simplelocation.h"


CpuRegisters::CpuRegisters()
{
  registers_.resize(RegisterFlags::SIZE);
  registers_.at(RegisterFlags::A) = 0x01;
  registers_.at(RegisterFlags::F) = 0xB0;
  registers_.at(RegisterFlags::B) = 0x00;
  registers_.at(RegisterFlags::C) = 0x13;
  registers_.at(RegisterFlags::D) = 0x00;
  registers_.at(RegisterFlags::E) = 0xD8;
  registers_.at(RegisterFlags::H) = 0x01;
  registers_.at(RegisterFlags::L) = 0x4D;
  registers_.at(RegisterFlags::SPu) = 0xFF;
  registers_.at(RegisterFlags::SPl) = 0xFF;
  registers_.at(RegisterFlags::PCu) = 0x01;
  registers_.at(RegisterFlags::PCl) = 0x00;
}

CpuRegisters::~CpuRegisters() = default;

LocationUP<uint16_t> CpuRegisters::af()
{
  return Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::F)),
                                      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::A)));
}

LocationUP<uint8_t> CpuRegisters::a()
{
  return Location<uint8_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::A)));
}

LocationUP<uint16_t> CpuRegisters::bc()
{
  return Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::C)),
                                      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::B)));
}

LocationUP<uint8_t> CpuRegisters::b()
{
  return Location<uint8_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::B)));
}

LocationUP<uint8_t> CpuRegisters::c()
{
  return Location<uint8_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::C)));
}

LocationUP<uint16_t> CpuRegisters::de()
{
  return Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::E)),
                                      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::D)));
}

LocationUP<uint8_t> CpuRegisters::d()
{
  return Location<uint8_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::D)));
}

LocationUP<uint8_t> CpuRegisters::e()
{
  return Location<uint8_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::E)));
}

LocationUP<uint16_t> CpuRegisters::hl()
{
  return Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::L)),
                                      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::H)));
}

LocationUP<uint8_t> CpuRegisters::h()
{
  return Location<uint8_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::H)));
}

LocationUP<uint8_t> CpuRegisters::l()
{
  return Location<uint8_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::L)));
}

LocationUP<uint16_t> CpuRegisters::sp()
{
  return Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::SPl)),
                                      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::SPu)));
}

LocationUP<uint16_t> CpuRegisters::pc()
{
  return Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::PCl)),
                                      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::PCu)));
}

FlagsView& CpuRegisters::getFlags()
{
  return *flags_;
}
