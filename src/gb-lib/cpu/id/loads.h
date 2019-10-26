#ifndef LOADS_H
#define LOADS_H

#include "cpu/cpu_defines.h"
#include "opcodeview.h"

namespace id {
namespace loads {

constexpr uint8_t BulkUpperMin = 0x4;
constexpr uint8_t BulkUpperMax = 0x7;

OperationUP bulkLoad(const OpcodeView opcode);

} // namespace loads
} // namespace id

#endif // LOADS_H
