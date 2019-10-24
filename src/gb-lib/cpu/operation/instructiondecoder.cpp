#include "instructiondecoder.h"

#include "loads.h"
#include "location/location.h"
#include "nop.h"
#include "opcodeview.h"
#include "operation.h"

OperationUP id::decode(LocationUP<uint8_t> opcodeLocation) {
  OpcodeView opcode(opcodeLocation->get());
  OperationUP result;
  if (opcode.value() == 0x00) {
    result = std::make_unique<Nop>();
  } else if (opcode.upperNibble() >= ops::BulkMinUpperNibble &&
             opcode.upperNibble() <= ops::BulkMaxUpperNibble) {
    result = ops::bulkLoad(opcode);
  } else {
    throw std::logic_error("Unknown opcode");
  }
  return result;
}