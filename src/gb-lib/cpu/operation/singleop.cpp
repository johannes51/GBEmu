#include "singleop.h"

#include <stdexcept>

#include "location/location.h"

void SingleOp::nextOpcode(Location<uint8_t> opcode)
{
  (void)opcode;
  throw std::logic_error("Single Opcode instruction");
}

auto SingleOp::isComplete() -> bool { return true; }

auto SingleOp::cycles() -> unsigned int { return 1; }
