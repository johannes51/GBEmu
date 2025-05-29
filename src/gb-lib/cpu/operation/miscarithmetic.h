#ifndef MISCARITHMETIC_H
#define MISCARITHMETIC_H

#include "singleop.h"

enum class MiscArithmeticFunction {
  DecimalAdjustA,
  ComplementA,
  ComplementCarry,
  SetCarry,
};

class MiscArithmetic : public SingleOp<1> {
public:
  MiscArithmetic(const MiscArithmeticFunction& function);

  void execute(RegistersInterface& registers, IMemoryWordView& memory) override;

private:
  MiscArithmeticFunction function_;
};

#endif // MISCARITHMETIC_H
