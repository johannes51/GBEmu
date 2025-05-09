#include "mockregisters.h"

MockRegisters::MockRegisters()
    : regs_()
{
}

auto MockRegisters::get(ByteRegister registerName) -> Register8UP
{
  (void)registerName;
  throw std::logic_error("Not implemented.");
  return Register8UP {};
}

auto MockRegisters::get(WordRegister registerName) -> Register16UP
{
  if (!regs_.contains(registerName)) {
    regs_.insert({ registerName, 0U });
  }
  return std::make_unique<Register16>(regs_[registerName]);
}

auto MockRegisters::getFlags() -> FlagsView& { return flags_; }

auto MockRegisters::getFlags() const -> const FlagsView& { return flags_; }
