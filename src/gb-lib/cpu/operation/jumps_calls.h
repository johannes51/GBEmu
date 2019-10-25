#ifndef JUMPS_CALLS_H
#define JUMPS_CALLS_H

#include "cpu/cpu_defines.h"
#include "opcodeview.h"

namespace ops {

constexpr uint8_t JumpDirect = 0xC3;
constexpr uint8_t JumpRelative = 0x18;

OperationUP jumpDirect();

} // namespace ops

#endif // JUMPS_CALLS_H
