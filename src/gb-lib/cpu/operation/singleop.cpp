#include "singleop.h"

#include <stdexcept>

#include "location/location.h"

void SingleOp::nextOpcode(Location<uint8_t> opcode)
{
  (void)opcode;
  throw std::logic_error("Single Opcode instruction");
}

bool SingleOp::isComplete() { return true; }

unsigned int SingleOp::cycles() { return 1; }
