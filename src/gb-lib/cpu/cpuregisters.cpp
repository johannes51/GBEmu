#include "cpuregisters.h"

#include "flagsview.h"
#include "location/location.h"
#include "location/registerbyte.h"
#include "registername.h"

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
  registers_.resize(RegisterName::SIZE);
  registers_.at(RegisterName::A) = INITIAL_A;
  registers_.at(RegisterName::F) = INITIAL_F;
  registers_.at(RegisterName::B) = INITIAL_B;
  registers_.at(RegisterName::C) = INITIAL_C;
  registers_.at(RegisterName::D) = INITIAL_D;
  registers_.at(RegisterName::E) = INITIAL_E;
  registers_.at(RegisterName::H) = INITIAL_H;
  registers_.at(RegisterName::L) = INITIAL_L;
  registers_.at(RegisterName::SPu) = INITIAL_SPu;
  registers_.at(RegisterName::SPl) = INITIAL_SPl;
  registers_.at(RegisterName::PCu) = INITIAL_PCu;
  registers_.at(RegisterName::PCl) = INITIAL_PCl;
}

CpuRegisters::~CpuRegisters() = default;

LocationUP<uint16_t> CpuRegisters::af() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::F)),
      std::make_unique<RegisterByte>(registers_.at(RegisterName::A)));
}

LocationUP<uint8_t> CpuRegisters::a() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::A)));
}

LocationUP<uint16_t> CpuRegisters::bc() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::C)),
      std::make_unique<RegisterByte>(registers_.at(RegisterName::B)));
}

LocationUP<uint8_t> CpuRegisters::b() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::B)));
}

LocationUP<uint8_t> CpuRegisters::c() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::C)));
}

LocationUP<uint16_t> CpuRegisters::de() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::E)),
      std::make_unique<RegisterByte>(registers_.at(RegisterName::D)));
}

LocationUP<uint8_t> CpuRegisters::d() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::D)));
}

LocationUP<uint8_t> CpuRegisters::e() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::E)));
}

LocationUP<uint16_t> CpuRegisters::hl() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::L)),
      std::make_unique<RegisterByte>(registers_.at(RegisterName::H)));
}

LocationUP<uint8_t> CpuRegisters::h() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::H)));
}

LocationUP<uint8_t> CpuRegisters::l() {
  return Location<uint8_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::L)));
}

LocationUP<uint16_t> CpuRegisters::sp() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::SPl)),
      std::make_unique<RegisterByte>(registers_.at(RegisterName::SPu)));
}

LocationUP<uint16_t> CpuRegisters::pc() {
  return Location<uint16_t>::generate(
      std::make_unique<RegisterByte>(registers_.at(RegisterName::PCl)),
      std::make_unique<RegisterByte>(registers_.at(RegisterName::PCu)));
}

FlagsView &CpuRegisters::getFlags() { return *flags_; }
