#include "cpuregisters.h"

#include "cpuflags.h"
#include "util/location.h"
#include "registerbyte.h"

#include "debug/simplelocation.h"


CpuRegisters::CpuRegisters()
{
  registers_[RegisterFlags::A] = 0;
  registers_[RegisterFlags::F] = 0;
  registers_[RegisterFlags::B] = 0;
  registers_[RegisterFlags::C] = 0;
  registers_[RegisterFlags::D] = 0;
  registers_[RegisterFlags::E] = 0;
  registers_[RegisterFlags::H] = 0;
  registers_[RegisterFlags::L] = 0;
  registers_[RegisterFlags::SPu] = 0;
  registers_[RegisterFlags::SPl] = 0;
  registers_[RegisterFlags::PCu] = 0x01;
  registers_[RegisterFlags::PCl] = 0x00;
  sp_ = Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_[RegisterFlags::SPl]),
      std::make_unique<RegisterByte>(registers_[RegisterFlags::SPu]));
  pc_ = Location<uint16_t>::generate(std::make_unique<RegisterByte>(registers_[RegisterFlags::PCl]),
      std::make_unique<RegisterByte>(registers_[RegisterFlags::PCu]));
  flags_ = std::make_unique<CpuFlags>(registers_[RegisterFlags::F]);
}

CpuRegisters::~CpuRegisters()
{
}

Location<uint16_t>& CpuRegisters::af()
{
  auto a = Location<uint16_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
}

Location<uint8_t>& CpuRegisters::a()
{
  auto a = Location<uint8_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
}

Location<uint16_t>& CpuRegisters::bc()
{
  auto a = Location<uint16_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
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
  auto a = Location<uint16_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
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
  auto a = Location<uint16_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  return *a;
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
  if (!sp_) {
    sp_ = Location<uint16_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  }
  return *sp_;
}

Location<uint16_t>& CpuRegisters::pc()
{
  if (!pc_) {
    pc_ = Location<uint16_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  }
  return *pc_;
}

FlagsView& CpuRegisters::getFlags()
{
  return *flags_;
}
