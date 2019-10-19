#include "cpuregisters.h"

#include "cpuflags.h"
#include "location/location.h"
#include "registerbyte.h"

#include "debug/simplelocation.h"


CpuRegisters::CpuRegisters()
{
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
  sp_ = Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::SPl)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::SPu)));
  pc_ = Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::PCl)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::PCu)));
  af_ = Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::F)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::A)));
  flags_ = std::make_unique<CpuFlags>(registers_.at(RegisterFlags::F));
  bc_ = Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::C)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::B)));
  de_ = Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::E)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::D)));
  hl_ = Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_.at(RegisterFlags::L)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::H)));
}

CpuRegisters::~CpuRegisters() {}

Location<uint16_t>& CpuRegisters::af()
{
  return *af_;
}

Location<uint8_t>& CpuRegisters::a()
{
  auto a = Location<uint8_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
}

Location<uint16_t>& CpuRegisters::bc()
{
  return *bc_;
}

Location<uint8_t>& CpuRegisters::b()
{
  auto a = Location<uint8_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
}

Location<uint8_t>& CpuRegisters::c()
{
  auto a = Location<uint8_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
}

Location<uint16_t>& CpuRegisters::de()
{
  return *de_;
}

Location<uint8_t>& CpuRegisters::d()
{
  auto a = Location<uint8_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
}

Location<uint8_t>& CpuRegisters::e()
{
  auto a = Location<uint8_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
}

Location<uint16_t>& CpuRegisters::hl()
{
  return *hl_;
}

Location<uint8_t>& CpuRegisters::h()
{
  auto a = Location<uint8_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
}

Location<uint8_t>& CpuRegisters::l()
{
  auto a = Location<uint8_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
}

Location<uint16_t>& CpuRegisters::sp()
{
  return *sp_;
}

Location<uint16_t>& CpuRegisters::pc()
{
  return *pc_;
}

FlagsView& CpuRegisters::getFlags()
{
  return *flags_;
}
