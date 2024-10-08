#include "wordaluoperation.h"

#include "location/location.h"
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
    apply(registers.getFlags(), ops::add<uint16_t>(*hl, *reg));
    break;
  }
  case WordAluFunction::Inc:
    ops::increment<uint16_t>(*reg);
    break;
  case WordAluFunction::Dec:
    ops::decrement<uint16_t>(*reg);
    break;
  }
}
