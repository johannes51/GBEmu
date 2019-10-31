#ifndef LOADS_H
#define LOADS_H

#include "cpu/cpu_defines.h"
#include "opcodeview.h"

namespace id {
namespace loads {

OperationUP bulkLoad(const OpcodeView opcode);
OperationUP loadImmediate(const OpcodeView opcode);
OperationUP loadRegisterIndirect(const OpcodeView opcode, bool store);

} // namespace loads
} // namespace id

#endif // LOADS_H
