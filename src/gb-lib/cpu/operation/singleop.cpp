#include "singleop.h"

#include "location/location.h"

void SingleOp::nextOpcode(Location<uint8_t> opcode)
{
  (void)opcode;
  throw std::logic_error("Single Opcode instruction");
}

bool SingleOp::isComplete() { return true; }

uint SingleOp::cycles() { return 1; }
