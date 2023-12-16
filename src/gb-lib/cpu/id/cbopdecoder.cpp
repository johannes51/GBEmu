#include "cbopdecoder.h"

#include "cpu/operation/cbop.h"
#include "cpu/operation/cbprefix.h"
#include "opcodeview.h"

auto CbOpDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.get() };
  if (indirect(opcode)) {
    return std::make_unique<CbOp>(function(opcode), true);
  } else {
    auto fun = function(opcode);
    auto op = std::make_unique<CbOp>(fun, false, operand(opcode));
    if (fun == CbFunction::Bit || fun == CbFunction::Set || fun == CbFunction::Reset) {
      op->setAffectedBit(bit(opcode));
    }
    return op;
  }
}

auto CbOpDecoder::decodedOpcodes() const -> std::vector<uint8_t> { return {}; }

auto CbOpDecoder::function(const OpcodeView& opcode) -> CbFunction
{
  if (opcode.upperNibble() >= 0xC) {
    return CbFunction::Set;
  } else if (opcode.upperNibble() >= 0x8) {
    return CbFunction::Reset;
  } else if (opcode.upperNibble() >= 0x4) {
    return CbFunction::Bit;
  } else {
    if (opcode.lowerNibble() <= 0x7) {
      if (opcode.upperNibble() == 0x0) {
        return CbFunction::RotateLeftCarry;
      } else if (opcode.upperNibble() == 0x1) {
        return CbFunction::RotateLeft;
      } else if (opcode.upperNibble() == 0x2) {
        return CbFunction::ShiftLeftArit;
      } else if (opcode.upperNibble() == 0x3) {
        return CbFunction::Swap;
      }
    } else {
      if (opcode.upperNibble() == 0x0) {
        return CbFunction::RotateRightCarry;
      } else if (opcode.upperNibble() == 0x1) {
        return CbFunction::RotateRight;
      } else if (opcode.upperNibble() == 0x2) {
        return CbFunction::ShiftRightArit;
      } else if (opcode.upperNibble() == 0x3) {
        return CbFunction::ShiftRightLogic;
      }
    }
  }
  throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
}

auto CbOpDecoder::indirect(const OpcodeView& opcode) -> bool
{
  return opcode.lowerNibble() == 0x6 || opcode.lowerNibble() == 0xE;
}

auto CbOpDecoder::operand(const OpcodeView& opcode) -> ByteRegister
{
  switch (opcode.lowerNibble()) {
  case 0x0:
  case 0x8:
    return ByteRegister::B;
    break;
  case 0x1:
  case 0x9:
    return ByteRegister::C;
    break;
  case 0x2:
  case 0xA:
    return ByteRegister::D;
    break;
  case 0x3:
  case 0xB:
    return ByteRegister::E;
    break;
  case 0x4:
  case 0xC:
    return ByteRegister::H;
    break;
  case 0x5:
  case 0xD:
    return ByteRegister::L;
    break;
  case 0x7:
  case 0xF:
    return ByteRegister::A;
    break;
  case 0x6:
  case 0xE:
  default:
    throw std::logic_error("Unimplemented");
    break;
  }
}

auto CbOpDecoder::bit(const OpcodeView& opcode) -> unsigned
{
  if (opcode.lowerNibble() <= 7) {
    switch (opcode.upperNibble()) {
    case 0x4:
    case 0x8:
    case 0xC:
      return 0;
      break;
    case 0x5:
    case 0x9:
    case 0xD:
      return 2;
      break;
    case 0x6:
    case 0xA:
    case 0xE:
      return 4;
      break;
    case 0x7:
    case 0xB:
    case 0xF:
      return 6;
      break;
    default:
      throw std::logic_error("Invalid opcode (non-bit instr).");
      break;
    }
  } else {
    switch (opcode.upperNibble()) {
    case 0x4:
    case 0x8:
    case 0xC:
      return 1;
      break;
    case 0x5:
    case 0x9:
    case 0xD:
      return 3;
      break;
    case 0x6:
    case 0xA:
    case 0xE:
      return 5;
      break;
    case 0x7:
    case 0xB:
    case 0xF:
      return 7;
      break;
    default:
      throw std::logic_error("Invalid opcode (non-bit instr).");
      break;
    }
  }
}
