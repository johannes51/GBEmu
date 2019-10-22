#ifndef OPERATION_H
#define OPERATION_H

#include <stdint.h>
#include <vector>

#include "location/location_defines.h"

class Operation {
public:
  Operation();
  virtual ~Operation() = default;
  DISABLE_COPY_AND_MOVE(Operation)

  virtual void nextOpcode(LocationUP<uint8_t> opcode) = 0;
  virtual bool isComplete() = 0;
  void clock();
  bool isDone();

  virtual void execute() = 0;

private:
  virtual uint cycles() = 0;

  uint clocks_;
};

#endif // OPERATION_H
