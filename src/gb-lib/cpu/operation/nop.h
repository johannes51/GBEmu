#ifndef NOP_H
#define NOP_H

#include "singleop.h"

class Nop final : public SingleOp {
private:
  void executeImpl(RegistersInterface& registers, IMemoryView& memory) override;
};

#endif // NOP_H
