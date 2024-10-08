#include "cbopdecoder.h"

#include "cpu/operation/cbop.h"
#include "opcodeview.h"

auto function(const OpcodeView& opcode) -> CbOp::CbFunction
{
  if (opcode.upperNibble() >= 0xC) {
    return CbOp::CbFunction::Set;
  } else if (opcode.upperNibble() >= 0x8) {
    return CbOp::CbFunction::Reset;
  } else if (opcode.upperNibble() >= 0x4) {
    return CbOp::CbFunction::Bit;
  } else {
    if (opcode.lowerNibble() <= 0x7) {
      if (opcode.upperNibble() == 0x0) {
        return CbOp::CbFunction::RotateLeftCarry;
      } else if (opcode.upperNibble() == 0x1) {
        return CbOp::CbFunction::RotateLeft;
      } else if (opcode.upperNibble() == 0x2) {
        return CbOp::CbFunction::ShiftLeftArithmetic;
      } else if (opcode.upperNibble() == 0x3) {
        return CbOp::CbFunction::Swap;
      }
    } else {
      if (opcode.upperNibble() == 0x0) {
        return CbOp::CbFunction::RotateRightCarry;
      } else if (opcode.upperNibble() == 0x1) {
        return CbOp::CbFunction::RotateRight;
      } else if (opcode.upperNibble() == 0x2) {
        return CbOp::CbFunction::ShiftRightArithmetic;
      } else if (opcode.upperNibble() == 0x3) {
        return CbOp::CbFunction::ShiftRightLogic;
      }
    }
  }
  throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
}

auto indirect(const OpcodeView& opcode) -> bool { return opcode.lowerNibble() == 0x6 || opcode.lowerNibble() == 0xE; }

auto operand(const OpcodeView& opcode) -> ByteRegister
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
    return ByteRegister::None;
    break;
  }
}

auto bit(const OpcodeView& opcode) -> unsigned
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
      return 8;
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
      return 8;
      break;
    }
  }
}

auto CbOpDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.getByte() };

  const auto fun = function(opcode);
  if (fun != CbOp::CbFunction::Bit && fun != CbOp::CbFunction::Set && fun != CbOp::CbFunction::Reset) {
    return std::make_unique<CbOp>(fun, operand(opcode), indirect(opcode));
  } else {
    auto result = std::make_unique<CbOp>(fun, operand(opcode), indirect(opcode));
    result->setAffectedBit(bit(opcode));
    return result;
  }
}
