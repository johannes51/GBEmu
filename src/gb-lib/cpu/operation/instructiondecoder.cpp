#include "instructiondecoder.h"

#include "location/location.h"
#include "nop.h"
#include "opcodeview.h"
#include "operation.h"

OperationUP id::decode(LocationUP<uint8_t> opcode) {
  OpcodeView op(opcode->get());
  OperationUP result;
  if (op.value() == 0x00) {
    result = std::make_unique<Nop>();
  } else {
    throw std::logic_error("Unknown opcode");
  }
  return result;
}
