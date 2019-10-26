#include "instructiondecoder.h"

#include "../operation/nop.h"
#include "../operation/operation.h"
#include "arithmetic.h"
#include "jumps_calls.h"
#include "loads.h"
#include "location/location.h"
#include "opcodeview.h"

OperationUP id::decode(Location<uint8_t> opcodeLocation)
{
  OpcodeView opcode(opcodeLocation.get());
  OperationUP result;
  if (opcode.value() == 0x00) {
    result = std::make_unique<Nop>();
  } else if (opcode.upperNibble() >= loads::BulkUpperMin && opcode.upperNibble() <= loads::BulkUpperMax) {
    result = loads::bulkLoad(opcode);
  } else if (opcode.upperNibble() >= arithmetic::BulkUpperMin && opcode.upperNibble() <= arithmetic::BulkUpperMax) {
    result = arithmetic::bulkArithmetic(opcode);
  } else if (opcode.value() == jumps_calls::JumpDirect) {
    result = jumps_calls::jumpDirect();
  } else {
    throw std::logic_error("Unknown opcode");
  }
  return result;
}
