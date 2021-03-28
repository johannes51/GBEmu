#ifndef NOP_H
#define NOP_H

#include "singleop.h"

enum class ControlOp { Nop, EI, DI };

class Control final : public SingleOp {
public:
  Control(ControlOp op);

  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  ControlOp op_;
};

#endif // NOP_H
