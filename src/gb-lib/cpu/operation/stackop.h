#ifndef STACKOP_H
#define STACKOP_H

#include "singleop.h"

#include "cpu/registersinterface.h"

class StackOp : public SingleOp {
public:
  explicit StackOp(bool isPush, WordRegisters target);

  unsigned int cycles(const RegistersInterface& registers) override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  bool push_;
  WordRegisters target_;
};

#endif // STACKOP_H
