#include "cpuregisters.h"

#include "cpuflags.h"
#include "location/location.h"
#include "location/registerbyte.h"

#include "debug/simplelocation.h"

const uint8_t INITIAL_A = 0x01;
const uint8_t INITIAL_F = 0xB0;
const uint8_t INITIAL_B = 0x00;
const uint8_t INITIAL_C = 0x13;
const uint8_t INITIAL_D = 0x00;
const uint8_t INITIAL_E = 0xD8;
const uint8_t INITIAL_H = 0x01;
const uint8_t INITIAL_L = 0x4D;
const uint8_t INITIAL_SPu = 0xFF;
const uint8_t INITIAL_SPl = 0xFF;
const uint8_t INITIAL_PCu = 0x01;
const uint8_t INITIAL_PCl = 0x00;

CpuRegisters::CpuRegisters() : registers_(), flags_() {
  registers_.resize(RegisterFlags::SIZE);
  registers_.at(RegisterFlags::A) = INITIAL_A;
  registers_.at(RegisterFlags::F) = INITIAL_F;
  registers_.at(RegisterFlags::B) = INITIAL_B;
  registers_.at(RegisterFlags::C) = INITIAL_C;
  registers_.at(RegisterFlags::D) = INITIAL_D;
  registers_.at(RegisterFlags::E) = INITIAL_E;
  registers_.at(RegisterFlags::H) = INITIAL_H;
  registers_.at(RegisterFlags::L) = INITIAL_L;
  registers_.at(RegisterFlags::SPu) = INITIAL_SPu;
  registers_.at(RegisterFlags::SPl) = INITIAL_SPl;
  registers_.at(RegisterFlags::PCu) = INITIAL_PCu;
  registers_.at(RegisterFlags::PCl) = INITIAL_PCl;
}

CpuRegisters::~CpuRegisters() = default;

LocationUP<uint16_t> CpuRegisters::af() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::F)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::A)));
}

LocationUP<uint8_t> CpuRegisters::a() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::A)));
}

LocationUP<uint16_t> CpuRegisters::bc() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::C)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::B)));
}

LocationUP<uint8_t> CpuRegisters::b() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::B)));
}

LocationUP<uint8_t> CpuRegisters::c() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::C)));
}

LocationUP<uint16_t> CpuRegisters::de() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::E)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::D)));
}

LocationUP<uint8_t> CpuRegisters::d() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::D)));
}

LocationUP<uint8_t> CpuRegisters::e() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::E)));
}

LocationUP<uint16_t> CpuRegisters::hl() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::L)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::H)));
}

LocationUP<uint8_t> CpuRegisters::h() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::H)));
}

LocationUP<uint8_t> CpuRegisters::l() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::L)));
}

LocationUP<uint16_t> CpuRegisters::sp() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::SPl)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::SPu)));
}

LocationUP<uint16_t> CpuRegisters::pc() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::PCl)),
      std::make_unique<RegisterByte>(registers_.at(RegisterFlags::PCu)));
}

FlagsView &CpuRegisters::getFlags() { return *flags_; }
