#include "jumps_calls.h"

#include "../operation/jump.h"

OperationUP id::jumps_calls::jumpDirect() { return std::make_unique<Jump>(JumpType::Direct); }
