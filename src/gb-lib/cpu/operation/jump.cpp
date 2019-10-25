#include "jump.h"

#include "location/location.h"

Jump::Jump(JumpType type) : operand_() {
  switch (type) {
  case JumpType::Direct:
    break;
  default:
    break;
  }
}

Jump::~Jump()
{

}

void Jump::nextOpcode(LocationUP<uint8_t> opcode) {}

bool Jump::isComplete() {}

uint Jump::cycles() { return 4; }

void Jump::executeImpl() {}
