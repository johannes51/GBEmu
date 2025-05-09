#include "cbopdecoder.h"

#include "cpu/operation/cbop.h"
#include "opcodeview.h"

auto function(const OpcodeView& opcode) -> CbOp::CbFunction
{
  if (opcode.upperNibble() >= 0xCU) {
    return CbOp::CbFunction::Set;
  } else if (opcode.upperNibble() >= 0x8U) {
    return CbOp::CbFunction::Reset;
  } else if (opcode.upperNibble() >= 0x4U) {
    return CbOp::CbFunction::Bit;
  } else {
    if (opcode.lowerNibble() <= 0x7U) {
      if (opcode.upperNibble() == 0x0U) {
        return CbOp::CbFunction::RotateLeftCarry;
      } else if (opcode.upperNibble() == 0x1U) {
        return CbOp::CbFunction::RotateLeft;
      } else if (opcode.upperNibble() == 0x2U) {
        return CbOp::CbFunction::ShiftLeftArithmetic;
      } else if (opcode.upperNibble() == 0x3U) {
        return CbOp::CbFunction::Swap;
      }
    } else {
      if (opcode.upperNibble() == 0x0U) {
        return CbOp::CbFunction::RotateRightCarry;
      } else if (opcode.upperNibble() == 0x1U) {
        return CbOp::CbFunction::RotateRight;
      } else if (opcode.upperNibble() == 0x2U) {
        return CbOp::CbFunction::ShiftRightArithmetic;
      } else if (opcode.upperNibble() == 0x3U) {
        return CbOp::CbFunction::ShiftRightLogic;
      }
    }
  }
  throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
}

auto indirect(const OpcodeView& opcode) -> bool { return opcode.lowerNibble() == 0x6U || opcode.lowerNibble() == 0xEU; }

auto operand(const OpcodeView& opcode) -> ByteRegister
{
  switch (opcode.lowerNibble()) {
  case 0x0U:
  case 0x8U:
    return ByteRegister::B;
    break;
  case 0x1U:
  case 0x9U:
    return ByteRegister::C;
    break;
  case 0x2U:
  case 0xAU:
    return ByteRegister::D;
    break;
  case 0x3U:
  case 0xBU:
    return ByteRegister::E;
    break;
  case 0x4U:
  case 0xCU:
    return ByteRegister::H;
    break;
  case 0x5U:
  case 0xDU:
    return ByteRegister::L;
    break;
  case 0x7U:
  case 0xFU:
    return ByteRegister::A;
    break;
  case 0x6U:
  case 0xEU:
  default:
    return ByteRegister::None;
    break;
  }
}

auto bit(const OpcodeView& opcode) -> unsigned
{
  if (opcode.lowerNibble() <= 7) {
    switch (opcode.upperNibble()) {
    case 0x4U:
    case 0x8U:
    case 0xCU:
      return 0;
      break;
    case 0x5U:
    case 0x9U:
    case 0xDU:
      return 2;
      break;
    case 0x6U:
    case 0xAU:
    case 0xEU:
      return 4;
      break;
    case 0x7U:
    case 0xBU:
    case 0xFU:
      return 6;
      break;
    default:
      return 8;
      break;
    }
  } else {
    switch (opcode.upperNibble()) {
    case 0x4U:
    case 0x8U:
    case 0xCU:
      return 1;
      break;
    case 0x5U:
    case 0x9U:
    case 0xDU:
      return 3;
      break;
    case 0x6U:
    case 0xAU:
    case 0xEU:
      return 5;
      break;
    case 0x7U:
    case 0xBU:
    case 0xFU:
      return 7;
      break;
    default:
      return 8;
      break;
    }
  }
}

auto CbOpDecoder::decode(const Location8& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.get() };

  const auto fun = function(opcode);
  if (fun != CbOp::CbFunction::Bit && fun != CbOp::CbFunction::Set && fun != CbOp::CbFunction::Reset) {
    return std::make_unique<CbOp>(fun, operand(opcode), indirect(opcode));
  } else {
    auto result = std::make_unique<CbOp>(fun, operand(opcode), indirect(opcode));
    result->setAffectedBit(bit(opcode));
    return result;
  }
}
