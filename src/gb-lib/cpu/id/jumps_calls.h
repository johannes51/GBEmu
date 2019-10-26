#ifndef JUMPS_CALLS_H
#define JUMPS_CALLS_H

#include "../cpu_defines.h"
#include "opcodeview.h"

namespace id {
namespace jumps_calls {

constexpr uint8_t JumpDirect = 0xC3;
constexpr uint8_t JumpRelative = 0x18;

OperationUP jumpDirect();

} // namespace jumps_calls
} // namespace id

#endif // JUMPS_CALLS_H
