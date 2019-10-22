#include "singleop.h"

void SingleOp::nextOpcode(LocationUP<uint8_t> opcode) {
  (void)opcode;
  throw std::logic_error("Single Opcode instruction");
}

bool SingleOp::isComplete() { return true; }

uint SingleOp::cycles() { return 1; }
