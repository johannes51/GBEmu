#ifndef OPERATION_H
#define OPERATION_H

#include <stdint.h>
#include <vector>

#include "cpu/cpu_defines.h"
#include "cpu/flagsview.h"
#include "location/location_defines.h"
#include "mem/mem_defines.h"
#include "ops/ops.h"

class Operation {
public:
  Operation() = default;
  virtual ~Operation() = default;
  DISABLE_COPY_AND_MOVE(Operation)

  virtual void showFlags(const FlagsView& flags) { (void)flags; }
  virtual void nextOpcode(Location<uint8_t> opcode) = 0;
  virtual bool isComplete() = 0;

  virtual unsigned cycles() = 0;
  virtual void execute(RegistersInterface& registers, IMemoryView& memory) = 0;

protected:
  static void apply(FlagsView& flags, const ops::OpResult& result)
  {
    if (result.z == ops::FlagResult::Reset) {
      flags.clearZero();
    } else if (result.z == ops::FlagResult::Set) {
      flags.setZero();
    }
    if (result.c == ops::FlagResult::Reset) {
      flags.clearCarry();
    } else if (result.c == ops::FlagResult::Set) {
      flags.setCarry();
    }
  }
};

#endif // OPERATION_H
