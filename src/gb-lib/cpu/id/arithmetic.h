#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "../cpu_defines.h"
#include "opcodeview.h"

namespace id {
namespace arithmetic {

constexpr uint8_t BulkUpperMin = 0x8;
constexpr uint8_t BulkUpperMax = 0xB;

OperationUP bulkArithmetic(const OpcodeView opcode);

} // namespace arithmetic
} // namespace id

#endif // ARITHMETIC_H
