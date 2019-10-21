#ifndef OPERATION_H
#define OPERATION_H

#include <stdint.h>
#include <vector>

#include "defines.h"

class Operation final {
public:
  Operation();
  DISABLE_COPY_AND_MOVE(Operation)

  bool nextOpcode(const uint8_t opcode);
  void clock();
  bool isDone();

private:
  std::vector<uint8_t> opcodes_;
};

#endif // OPERATION_H
