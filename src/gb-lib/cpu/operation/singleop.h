#ifndef SINGLEOP_H
#define SINGLEOP_H

#include "operation.h"

#include <stdexcept>

template <unsigned Cycles> class SingleOp : public Operation {
public:
  virtual ~SingleOp() = default;

  virtual void nextOpcode(LocationUP opcode) override
  {
    (void)opcode;
    throw std::logic_error("Single Opcode instruction");
  }
  virtual bool isComplete() override { return true; }

  virtual unsigned cycles() override { return Cycles; }
};

#endif // SINGLEOP_H
