#include "mockregisters.h"

#include "mem/registers/register16.h"

MockRegisters::MockRegisters()
    : regs_()
{
}

auto MockRegisters::get(ByteRegister registerName) -> Location8
{
  (void)registerName;
  throw std::logic_error("Not implemented.");
  return { nullptr };
}

auto MockRegisters::get(WordRegister registerName) -> Location16
{
  if (!regs_.contains(registerName)) {
    regs_.insert({ registerName, 0U });
  }
  return { std::make_unique<Register16>(regs_[registerName]) };
}

auto MockRegisters::getFlags() -> FlagsView& { return flags_; }

auto MockRegisters::getFlags() const -> const FlagsView& { return flags_; }
