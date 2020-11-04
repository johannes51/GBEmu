#ifndef SINGLEOP_H
#define SINGLEOP_H

#include "operation.h"

class SingleOp : public Operation {
public:
  virtual ~SingleOp() = default;

  virtual void nextOpcode(Location<uint8_t> opcode) override;
  virtual bool isComplete() override;

  virtual unsigned int cycles() override;
};

#endif // SINGLEOP_H
