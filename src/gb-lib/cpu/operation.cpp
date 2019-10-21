#include "operation.h"

#include "location/location.h"

Operation::Operation() : opcodes_() {}

bool Operation::nextOpcode(LocationUP<uint8_t> opcode) {
  opcodes_.push_back(opcode->get());
  return false;
}

void Operation::clock() {}

bool Operation::isDone() { return true; }
