#include "wordaluoperation.h"

#include "mem/location8.h"
#include "ops/arithmetic.h"

WordAluOperation::WordAluOperation(WordAluFunction function, WordRegister targetRegister)
    : function_(function)
    , register_(targetRegister)
{
}

void WordAluOperation::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  auto reg = registers.get(register_);
  switch (function_) {
  case WordAluFunction::Add: {
    auto hl = registers.get(WordRegister::HL);
    apply(registers.getFlags(), ops::add(hl, reg));
    break;
  }
  case WordAluFunction::Inc:
    ops::increment(reg);
    break;
  case WordAluFunction::Dec:
    ops::decrement(reg);
    break;
  }
}
