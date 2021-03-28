#include "jumps_calls.h"

#include "../operation/jump.h"

auto id::jumps_calls::jumpDirect() -> OperationUP { return std::make_unique<Jump>(JumpType::Direct); }
