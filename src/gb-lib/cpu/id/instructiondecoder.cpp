#include "instructiondecoder.h"

#include "../operation/nop.h"
#include "../operation/operation.h"
#include "arithmetic.h"
#include "jumps_calls.h"
#include "loads.h"
#include "location/location.h"
#include "opcodeview.h"

OperationUP id::decode(const Location<uint8_t> opcodeLocation)
{
  const OpcodeView opcode(opcodeLocation.get());
  OperationUP result;
  if (opcode.value() == 0x00) {
    result = std::make_unique<Nop>();
  } else if (opcode.upperNibble() <= 0x3) {
    if (opcode.lowerNibble() == 0x1 || opcode.lowerNibble() == 0x6 || opcode.lowerNibble() == 0xE) {
      result = loads::loadImmediate(opcode);
    } else if (opcode.lowerNibble() == 0x2) {
      result = loads::loadRegisterIndirect(opcode, true);
    } else if (opcode.lowerNibble() == 0xA) {
      result = loads::loadRegisterIndirect(opcode, false);
    } else {
      throw std::logic_error("Unimplemented");
    }
  } else if (opcode.upperNibble() >= 0x4 && opcode.upperNibble() <= 0x7) {
    result = loads::bulkLoad(opcode);
  } else if (opcode.upperNibble() >= 0x8 && opcode.upperNibble() <= 0xB) {
    result = arithmetic::bulkArithmetic(opcode);
  } else if (opcode.value() == jumps_calls::JumpDirect) {
    result = jumps_calls::jumpDirect();
  } else {
    throw std::logic_error("Unknown opcode");
  }
  return result;
}
