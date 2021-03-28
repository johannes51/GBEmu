#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "../cpu_defines.h"
#include "opcodeview.h"

namespace id {
namespace arithmetic {

OperationUP bulkArithmetic(const OpcodeView opcode);

} // namespace arithmetic
} // namespace id

#endif // ARITHMETIC_H
