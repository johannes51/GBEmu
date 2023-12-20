#include "miscarithmetic.h"

#include "../registersinterface.h"
#include "ops/arithmetic.h"

MiscArithmetic::MiscArithmetic(const MiscArithmeticFunction& function)
    : function_(function)
{
}

void MiscArithmetic::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  switch (function_) {
  case MiscArithmeticFunction::DecimalAdjustA: {
    auto reg = registers.get(ByteRegister::A);
    apply(registers.getFlags(), ops::decimalAdjust(reg));
    break;
  }
  case MiscArithmeticFunction::ComplementA: {
    auto reg = registers.get(ByteRegister::A);
    apply(registers.getFlags(), ops::complement(reg));
    break;
  }
  case MiscArithmeticFunction::ComplementCarry: {
    auto& flags = registers.getFlags();
    if (flags.carry()) {
      flags.clearCarry();
    } else {
      flags.setCarry();
    }
    break;
  }
  case MiscArithmeticFunction::SetCarry: {
    registers.getFlags().setCarry();
    break;
  }
  }
}
