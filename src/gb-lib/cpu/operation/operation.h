#ifndef OPERATION_H
#define OPERATION_H

#include <memory>

#include "../registers/registersinterface.h"
#include "mem/ilocation8.h"
#include "mem/imemorywordview.h"
#include "ops/ops.h"

class Operation {
public:
  Operation() = default;
  virtual ~Operation() = default;
  DISABLE_COPY_AND_MOVE(Operation)

  virtual void showFlags(const FlagsView& flags) { (void)flags; }
  virtual void nextOpcode(const ILocation8& opcode) = 0;
  virtual bool isComplete() = 0;

  virtual unsigned cycles() = 0;
  virtual void execute(RegistersInterface& registers, IMemoryWordView& memory) = 0;

protected:
  static void apply(FlagsView& flags, const ops::OpResult& result)
  {
    if (result.z == ops::FlagResult::Reset) {
      flags.clearZero();
    } else if (result.z == ops::FlagResult::Set) {
      flags.setZero();
    }
    if (result.n == ops::FlagResult::Reset) {
      flags.clearSubtract();
    } else if (result.n == ops::FlagResult::Set) {
      flags.setSubtract();
    }
    if (result.h == ops::FlagResult::Reset) {
      flags.clearHalfCarry();
    } else if (result.h == ops::FlagResult::Set) {
      flags.setHalfCarry();
    }
    if (result.c == ops::FlagResult::Reset) {
      flags.clearCarry();
    } else if (result.c == ops::FlagResult::Set) {
      flags.setCarry();
    }
  }
};

using OperationUP = std::unique_ptr<Operation>;

#endif // OPERATION_H
