#ifndef SINGLEOP_H
#define SINGLEOP_H

#include "operation.h"

class SingleOp : public Operation {
public:
  virtual void nextOpcode(Location<uint8_t> opcode) override;
  virtual bool isComplete() override;

private:
  virtual uint cycles() override;
};

#endif // SINGLEOP_H
