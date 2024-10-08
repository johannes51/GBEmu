#include "cpuregisters.h"

#include <stdexcept>

#include "cpuflags.h"

const std::unordered_map<ByteRegister, std::pair<WordRegister, bool>> CpuRegisters::Mappings {
  { ByteRegister::A, std::make_pair(WordRegister::AF, true) },
  { ByteRegister::F, std::make_pair(WordRegister::AF, false) },
  { ByteRegister::B, std::make_pair(WordRegister::BC, true) },
  { ByteRegister::C, std::make_pair(WordRegister::BC, false) },
  { ByteRegister::D, std::make_pair(WordRegister::DE, true) },
  { ByteRegister::E, std::make_pair(WordRegister::DE, false) },
  { ByteRegister::H, std::make_pair(WordRegister::HL, true) },
  { ByteRegister::L, std::make_pair(WordRegister::HL, false) }
};

CpuRegisters::CpuRegisters()
    : registers_()
    , flags_()
{
  registers_[WordRegister::AF] = static_cast<uint16_t>(INITIAL_A) << 8 | INITIAL_F;
  registers_[WordRegister::BC] = static_cast<uint16_t>(INITIAL_B) << 8 | INITIAL_C;
  registers_[WordRegister::DE] = static_cast<uint16_t>(INITIAL_D) << 8 | INITIAL_E;
  registers_[WordRegister::HL] = static_cast<uint16_t>(INITIAL_H) << 8 | INITIAL_L;
  registers_[WordRegister::SP] = static_cast<uint16_t>(INITIAL_SPu) << 8 | INITIAL_SPl;
  registers_[WordRegister::PC] = static_cast<uint16_t>(INITIAL_PCu) << 8 | INITIAL_PCl;
  flags_ = std::make_unique<CpuFlags>(get(ByteRegister::F)->getReference());
}

auto CpuRegisters::get(ByteRegister registerName) -> RegisterUP
{
  if (!Mappings.contains(registerName)) {
    throw std::invalid_argument("Unable to provide register");
  }
  const auto& mapping = Mappings.at(registerName);
  return std::make_unique<Register>(registers_[mapping.first], mapping.second);
}

auto CpuRegisters::get(WordRegister registerName) -> RegisterUP
{
  return std::make_unique<Register>(registers_.at(registerName));
}

CpuRegisters::~CpuRegisters() = default;

auto CpuRegisters::getFlags() -> FlagsView& { return *flags_; }

auto CpuRegisters::getFlags() const -> const FlagsView& { return *flags_; }
