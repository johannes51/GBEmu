#include "wordaluoperation.h"

#include "location/location.h"
#include "util/ops.h"

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

void WordAluOperation::apply(FlagsView& flags, const ops::OpResult& result)
{
  (void)flags;
  (void)result;
  //  TODO: deal with flags
}
