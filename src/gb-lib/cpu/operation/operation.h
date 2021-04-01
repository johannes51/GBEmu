#ifndef OPERATION_H
#define OPERATION_H

#include <stdint.h>
#include <vector>

#include "cpu/cpu_defines.h"
#include "location/location_defines.h"
#include "mem/mem_defines.h"

class Operation {
public:
  Operation() = default;
  virtual ~Operation() = default;
  DISABLE_COPY_AND_MOVE(Operation)

  virtual void nextOpcode(Location<uint8_t> opcode) = 0;
  virtual bool isComplete() = 0;

  virtual unsigned int cycles(const RegistersInterface& registers) = 0;
  virtual void execute(RegistersInterface& registers, IMemoryView& memory) = 0;
};

#endif // OPERATION_H
