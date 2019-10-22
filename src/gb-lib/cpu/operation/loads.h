#ifndef LOADS_H
#define LOADS_H

#include "cpu/cpu_defines.h"
#include "opcodeview.h"

namespace ops {

constexpr uint8_t BulkMinUpperNibble = 0x4;
constexpr uint8_t BulkMaxUpperNibble = 0x7;

OperationUP bulkLoad(const OpcodeView opcode);

} // namespace ops

#endif // LOADS_H
