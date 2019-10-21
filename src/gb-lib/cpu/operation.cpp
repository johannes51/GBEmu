#include "operation.h"

bool Operation::nextOpcode(const uint8_t opcode) {
  opcodes_.push_back(opcode);
  return false;
}

void Operation::clock() {}

bool Operation::isDone() { return true; }
