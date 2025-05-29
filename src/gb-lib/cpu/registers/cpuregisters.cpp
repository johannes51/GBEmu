#include "cpuregisters.h"

#include <stdexcept>

#include "constants.h"
#include "cpuflags.h"

CpuRegisters::CpuRegisters()
    : registers_()
    , flags_()
{
  registers_[WordRegister::AF] = static_cast<unsigned>(INITIAL_A) << BYTE_SHIFT | INITIAL_F;
  registers_[WordRegister::BC] = static_cast<unsigned>(INITIAL_B) << BYTE_SHIFT | INITIAL_C;
  registers_[WordRegister::DE] = static_cast<unsigned>(INITIAL_D) << BYTE_SHIFT | INITIAL_E;
  registers_[WordRegister::HL] = static_cast<unsigned>(INITIAL_H) << BYTE_SHIFT | INITIAL_L;
  registers_[WordRegister::SP] = static_cast<unsigned>(INITIAL_SPu) << BYTE_SHIFT | INITIAL_SPl;
  registers_[WordRegister::PC] = static_cast<unsigned>(INITIAL_PCu) << BYTE_SHIFT | INITIAL_PCl;

  wordRegisterMappings_.emplace(WordRegister::AF, registers_[WordRegister::AF]);
  wordRegisterMappings_.emplace(WordRegister::BC, registers_[WordRegister::BC]);
  wordRegisterMappings_.emplace(WordRegister::DE, registers_[WordRegister::DE]);
  wordRegisterMappings_.emplace(WordRegister::HL, registers_[WordRegister::HL]);
  wordRegisterMappings_.emplace(WordRegister::SP, registers_[WordRegister::SP]);
  wordRegisterMappings_.emplace(WordRegister::PC, registers_[WordRegister::PC]);

  byteRegisterMappings_.emplace(std::piecewise_construct, std::forward_as_tuple(ByteRegister::A),
      std::forward_as_tuple(registers_[WordRegister::AF], true));
  byteRegisterMappings_.emplace(std::piecewise_construct, std::forward_as_tuple(ByteRegister::A),
      std::forward_as_tuple(registers_[WordRegister::AF], true));
  byteRegisterMappings_.emplace(std::piecewise_construct, std::forward_as_tuple(ByteRegister::F),
      std::forward_as_tuple(registers_[WordRegister::AF], false));
  byteRegisterMappings_.emplace(std::piecewise_construct, std::forward_as_tuple(ByteRegister::B),
      std::forward_as_tuple(registers_[WordRegister::BC], true));
  byteRegisterMappings_.emplace(std::piecewise_construct, std::forward_as_tuple(ByteRegister::C),
      std::forward_as_tuple(registers_[WordRegister::BC], false));
  byteRegisterMappings_.emplace(std::piecewise_construct, std::forward_as_tuple(ByteRegister::D),
      std::forward_as_tuple(registers_[WordRegister::DE], true));
  byteRegisterMappings_.emplace(std::piecewise_construct, std::forward_as_tuple(ByteRegister::E),
      std::forward_as_tuple(registers_[WordRegister::DE], false));
  byteRegisterMappings_.emplace(std::piecewise_construct, std::forward_as_tuple(ByteRegister::H),
      std::forward_as_tuple(registers_[WordRegister::HL], true));
  byteRegisterMappings_.emplace(std::piecewise_construct, std::forward_as_tuple(ByteRegister::L),
      std::forward_as_tuple(registers_[WordRegister::HL], false));

  flags_ = std::make_unique<CpuFlags>(*reinterpret_cast<uint8_t*>(&registers_[WordRegister::AF]));
}

auto CpuRegisters::get(ByteRegister registerName) -> ILocation8&
{
  auto it = byteRegisterMappings_.find(registerName);
  if (it == byteRegisterMappings_.end()) {
    throw std::invalid_argument("Non-existent byte selected.");
  }
  return it->second;
}

auto CpuRegisters::get(WordRegister registerName) -> ILocation16&
{
  auto it = wordRegisterMappings_.find(registerName);
  if (it == wordRegisterMappings_.end()) {
    throw std::invalid_argument("Non-existent word selected.");
  }
  return it->second;
}

CpuRegisters::~CpuRegisters() = default;

auto CpuRegisters::getFlags() -> FlagsView& { return *flags_; }

auto CpuRegisters::getFlags() const -> const FlagsView& { return *flags_; }
