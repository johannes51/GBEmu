#include "mockregisters.h"

MockRegisters::MockRegisters()
    : regs_()
{
}

auto MockRegisters::get(ByteRegister registerName) -> ILocation8&
{
  (void)registerName;
  throw std::logic_error("Not implemented.");
}

auto MockRegisters::get(WordRegister registerName) -> ILocation16&
{
  if (!regs_.contains(registerName)) {
    regs_.insert({ registerName, 0U });
  }
  reg_ = std::make_unique<Register16>(regs_[registerName]);
  return *reg_;
}

auto MockRegisters::getFlags() -> FlagsView& { return flags_; }

auto MockRegisters::getFlags() const -> const FlagsView& { return flags_; }
