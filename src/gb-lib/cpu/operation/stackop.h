#ifndef STACKOP_H
#define STACKOP_H

#include "singleop.h"

#include "cpu/registersinterface.h"

class StackOp : public SingleOp {
public:
  explicit StackOp(bool isPush, WordRegister target);

  unsigned int cycles(const RegistersInterface& registers) override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  bool push_;
  WordRegister target_;
};

#endif // STACKOP_H
