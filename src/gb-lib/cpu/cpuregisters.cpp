#include "cpuregisters.h"

#include <stdexcept>

#include "cpuflags.h"
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
  flags_ = std::make_unique<CpuFlags>(registers_[RegisterName::F]);
}

CpuRegisters::~CpuRegisters() = default;

auto CpuRegisters::get(ByteRegister registerName) -> Location<uint8_t>
{
  auto byte = RegisterName::A;
  switch (registerName) {
  case ByteRegister::A:
    byte = RegisterName::A;
    break;
  case ByteRegister::B:
    byte = RegisterName::B;
    break;
  case ByteRegister::C:
    byte = RegisterName::C;
    break;
  case ByteRegister::D:
    byte = RegisterName::D;
    break;
  case ByteRegister::E:
    byte = RegisterName::E;
    break;
  case ByteRegister::H:
    byte = RegisterName::H;
    break;
  case ByteRegister::L:
    byte = RegisterName::L;
    break;
  case ByteRegister::None:
  default:
    throw std::invalid_argument("Unable to provide register");
    break;
  }
  return Location<uint8_t>::generate(std::make_unique<RamByte>(registers_.at(byte)));
}

auto CpuRegisters::get(WordRegister registerName) -> Location<uint16_t>
{
  auto lower = RegisterName::PCl;
  auto upper = RegisterName::PCu;
  switch (registerName) {
  case WordRegister::AF:
    lower = RegisterName::F;
    upper = RegisterName::A;
    break;
  case WordRegister::BC:
    lower = RegisterName::C;
    upper = RegisterName::B;
    break;
  case WordRegister::DE:
    lower = RegisterName::E;
    upper = RegisterName::D;
    break;
  case WordRegister::HL:
    lower = RegisterName::L;
    upper = RegisterName::H;
    break;
  case WordRegister::SP:
    lower = RegisterName::SPl;
    upper = RegisterName::SPu;
    break;
  case WordRegister::PC:
    lower = RegisterName::PCl;
    upper = RegisterName::PCu;
    break;
  case WordRegister::None:
  default:
    throw std::invalid_argument("Unable to provide register");
    break;
  }
  return Location<uint16_t>::generate(
      std::make_unique<RamByte>(registers_.at(lower)), std::make_unique<RamByte>(registers_.at(upper)));
}

auto CpuRegisters::getFlags() -> FlagsView& { return *flags_; }

auto CpuRegisters::getFlags() const -> const FlagsView& { return *flags_; }
