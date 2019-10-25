#include "jumps_calls.h"

#include "jump.h"

OperationUP ops::jumpDirect() {
  return std::make_unique<Jump>(JumpType::Direct);
}
