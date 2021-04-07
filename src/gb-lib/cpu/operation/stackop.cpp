#include "stackop.h"

#include "mem/imemoryview.h"
#include "util/helpers.h"
#include "util/ops.h"

StackOp::StackOp(bool isPush, WordRegister target)
    : push_(isPush)
    , target_(target)
{
}

auto StackOp::cycles(const RegistersInterface& registers) -> unsigned int
{
  (void)registers;
  return push_ ? 4 : 3;
}

void StackOp::execute(RegistersInterface& registers, IMemoryView& memory)
{
  auto reg = registers.get(target_);
  auto sp = registers.get(WordRegister::SP);
  if (push_) {
    ops::decrement(sp);
    ops::decrement(sp);
    auto memLoc = memory.getWord(hlp::indirect(sp));
    ops::load(memLoc, reg);
  }
  if (!push_) {
    ops::load(reg, memory.getWord(hlp::indirect(sp)));
    ops::increment(sp);
    ops::increment(sp);
    if (target_ == WordRegister::AF) {
      // TODO: sort out flags
    }
  }
}
