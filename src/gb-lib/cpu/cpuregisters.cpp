#include "cpuregisters.h"

#include <stdexcept>

#include "constants.h"
#include "cpuflags.h"
#include "mem/registers/register16.h"
#include "mem/registers/register8.h"

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
  registers_[WordRegister::AF] = static_cast<unsigned int>(INITIAL_A) << BYTE_SHIFT | INITIAL_F;
  registers_[WordRegister::BC] = static_cast<unsigned int>(INITIAL_B) << BYTE_SHIFT | INITIAL_C;
  registers_[WordRegister::DE] = static_cast<unsigned int>(INITIAL_D) << BYTE_SHIFT | INITIAL_E;
  registers_[WordRegister::HL] = static_cast<unsigned int>(INITIAL_H) << BYTE_SHIFT | INITIAL_L;
  registers_[WordRegister::SP] = static_cast<unsigned int>(INITIAL_SPu) << BYTE_SHIFT | INITIAL_SPl;
  registers_[WordRegister::PC] = static_cast<unsigned int>(INITIAL_PCu) << BYTE_SHIFT | INITIAL_PCl;

  flags_ = std::make_unique<CpuFlags>(*reinterpret_cast<uint8_t*>(&registers_[WordRegister::AF]));
}

auto CpuRegisters::get(ByteRegister registerName) -> Location8
{
  if (!Mappings.contains(registerName)) {
    throw std::invalid_argument("Unable to provide register");
  }
  const auto& mapping = Mappings.at(registerName);
  return { std::make_unique<Register8>(registers_[mapping.first], mapping.second) };
}

auto CpuRegisters::get(WordRegister registerName) -> Location16
{
  return { std::make_unique<Register16>(registers_.at(registerName)) };
}

CpuRegisters::~CpuRegisters() = default;

auto CpuRegisters::getFlags() -> FlagsView& { return *flags_; }

auto CpuRegisters::getFlags() const -> const FlagsView& { return *flags_; }
