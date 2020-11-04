#include "cpuregisters.h"

#include <stdexcept>

#include "flagsview.h"
#include "location/location.h"
#include "location/rambyte.h"

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

CpuRegisters::CpuRegisters()
    : registers_()
    , flags_()
{
  registers_[RegisterName::A] = INITIAL_A;
  registers_[RegisterName::F] = INITIAL_F;
  registers_[RegisterName::B] = INITIAL_B;
  registers_[RegisterName::C] = INITIAL_C;
  registers_[RegisterName::D] = INITIAL_D;
  registers_[RegisterName::E] = INITIAL_E;
  registers_[RegisterName::H] = INITIAL_H;
  registers_[RegisterName::L] = INITIAL_L;
  registers_[RegisterName::SPu] = INITIAL_SPu;
  registers_[RegisterName::SPl] = INITIAL_SPl;
  registers_[RegisterName::PCu] = INITIAL_PCu;
  registers_[RegisterName::PCl] = INITIAL_PCl;
}

Location<uint16_t> CpuRegisters::get(WordRegisters registerName)
{
  auto lower = RegisterName::PCl;
  auto upper = RegisterName::PCu;
  switch (registerName) {
  case WordRegisters::AF:
    lower = RegisterName::F;
    upper = RegisterName::A;
    break;
  case WordRegisters::BC:
    lower = RegisterName::C;
    upper = RegisterName::B;
    break;
  case WordRegisters::DE:
    lower = RegisterName::E;
    upper = RegisterName::D;
    break;
  case WordRegisters::HL:
    lower = RegisterName::L;
    upper = RegisterName::H;
    break;
  case WordRegisters::SP:
    lower = RegisterName::SPl;
    upper = RegisterName::SPu;
    break;
  case WordRegisters::PC:
    lower = RegisterName::PCl;
    upper = RegisterName::PCu;
    break;
  case WordRegisters::None:
  default:
    throw std::invalid_argument("Unable to provide register");
    break;
  }
  return Location<uint16_t>::generate(
      std::make_unique<RamByte>(registers_.at(lower)), std::make_unique<RamByte>(registers_.at(upper)));
}

Location<uint8_t> CpuRegisters::get(ByteRegisters registerName)
{
  auto byte = RegisterName::A;
  switch (registerName) {
  case ByteRegisters::A:
    byte = RegisterName::A;
    break;
  case ByteRegisters::B:
    byte = RegisterName::B;
    break;
  case ByteRegisters::C:
    byte = RegisterName::C;
    break;
  case ByteRegisters::D:
    byte = RegisterName::D;
    break;
  case ByteRegisters::E:
    byte = RegisterName::E;
    break;
  case ByteRegisters::H:
    byte = RegisterName::H;
    break;
  case ByteRegisters::L:
    byte = RegisterName::L;
    break;
  case ByteRegisters::None:
  default:
    throw std::invalid_argument("Unable to provide register");
    break;
  }
  return Location<uint8_t>::generate(std::make_unique<RamByte>(registers_.at(byte)));
}

CpuRegisters::~CpuRegisters() = default;

FlagsView& CpuRegisters::getFlags() { return *flags_; }
