#include "mockregisters.h"

MockRegisters::MockRegisters()
    : regs_()
{
}

auto MockRegisters::get(ByteRegister registerName) -> RegisterUP
{
  (void)registerName;
  throw std::logic_error("Not implemented.");
  return RegisterUP {};
}

auto MockRegisters::get(WordRegister registerName) -> RegisterUP
{
  if (!regs_.contains(registerName)) {
    regs_.insert({ registerName, 0U });
  }
  return std::make_unique<Register>(regs_[registerName]);
}

auto MockRegisters::getFlags() -> FlagsView&
{
  throw std::logic_error("Not implemented.");
  return *(FlagsView*)(nullptr);
}

auto MockRegisters::getFlags() const -> const FlagsView&
{
  throw std::logic_error("Not implemented.");
  return *(FlagsView*)(nullptr);
}
