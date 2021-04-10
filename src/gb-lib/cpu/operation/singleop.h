#ifndef SINGLEOP_H
#define SINGLEOP_H

#include "operation.h"

#include <stdexcept>

#include "location/location.h"

template <unsigned Cycles> class SingleOp : public Operation {
public:
  virtual ~SingleOp() = default;

  virtual void nextOpcode(Location<uint8_t> opcode) override;
  virtual bool isComplete() override { return true; }

  virtual unsigned cycles(const RegistersInterface& registers) override;
};

template <unsigned Cycles> void SingleOp<Cycles>::nextOpcode(Location<uint8_t> opcode)
{
  (void)opcode;
  throw std::logic_error("Single Opcode instruction");
}

template <unsigned Cycles> unsigned SingleOp<Cycles>::cycles(const RegistersInterface& registers)
{
  (void)registers;
  return Cycles;
}

#endif // SINGLEOP_H
