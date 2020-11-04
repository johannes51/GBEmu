#include "instructiondecoder.h"

#include <stdexcept>

#include "../operation/nop.h"
#include "../operation/operation.h"
#include "arithmetic.h"
#include "jumps_calls.h"
#include "loads.h"
#include "location/location.h"
#include "opcodeview.h"

OperationUP decode0xTo3x(const OpcodeView& opcode)
{
  OperationUP result;
  switch (opcode.lowerNibble()) {
  case 0x1:
  case 0x6:
  case 0xE:
    result = id::loads::loadImmediate(opcode);
    break;
  case 0x5:
    result = id::arithmetic::decrement(opcode);
    break;
  case 0x2:
    result = id::loads::loadRegisterIndirect(opcode, true);
  break;
  case 0xA:
    result = id::loads::loadRegisterIndirect(opcode, false);
  break;
  case 0x0:
  case 0x3:
  case 0x4:
  case 0x7:
  case 0x8:
  case 0x9:
  case 0xB:
  case 0xC:
  case 0xD:
  case 0xF:
    throw std::logic_error("Unimplemented");
  break;
  }
  return result;
}

OperationUP id::decode(const Location<uint8_t> opcodeLocation)
{
  const OpcodeView opcode(opcodeLocation.get());
  OperationUP result;
  if (opcode.value() == 0x00) {
    result = std::make_unique<Nop>();
  } else if (opcode.value() == jumps_calls::JumpDirect) {
    result = jumps_calls::jumpDirect();
  } else { switch (opcode.upperNibble()) {
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
      result = decode0xTo3x(opcode);
      break;
    case 0x4:
    case 0x5:
    case 0x6:
    case 0x7:
      result = loads::bulkLoad(opcode);
      break;
    case 0x8:
    case 0x9:
    case 0xA:
    case 0xB:
      result = arithmetic::bulkArithmetic(opcode);
      break;
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
      throw std::invalid_argument("Unknown opcode");
      break;
    } }

  return result;
}
