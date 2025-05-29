#ifndef PUSH_POP_H
#define PUSH_POP_H

#include "singleop.h"

#include "cpu/registers/registersinterface.h"

class PushPop final : public SingleOp<0> {
public:
  enum class Direction { Push, Pop, Invalid };

  PushPop(Direction direction, WordRegister targetRegister);
  ~PushPop() override = default;

  unsigned cycles() override;
  void execute(RegistersInterface& registers, IMemoryWordView& memory) override;

private:
  const Direction direction_;
  WordRegister targetRegister_;
};

#endif // PUSH_POP_H
