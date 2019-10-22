#ifndef NOP_H
#define NOP_H

#include "singleop.h"

class Nop final : public SingleOp {
public:
  void execute() override;
};

#endif // NOP_H
