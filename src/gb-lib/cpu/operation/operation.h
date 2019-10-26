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

  virtual void nextOpcode(Location<uint8_t> opcode) = 0;
  virtual bool isComplete() = 0;
  void clock();
  bool isDone();

  void execute();

private:
  virtual uint cycles() = 0;
  virtual void executeImpl() = 0;

  uint clocks_;
};

#endif // OPERATION_H
