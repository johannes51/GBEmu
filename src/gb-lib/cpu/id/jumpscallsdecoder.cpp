#include "jumpscallsdecoder.h"

#include <stdexcept>

#include "cpu/operation/jump.h"

auto JumpsCallsDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  OpcodeView opcode { opcodeLocation.get() };
  if (opcode.upperNibble() <= 0x3) {
    return std::make_unique<Jump>(JumpType::Regular, TargetType::Relative, condition(opcode));
  } else {
    return std::make_unique<Jump>(type(opcode), TargetType::Absolute, condition(opcode));
  }
  throw std::logic_error("Unhandled opcode: " + std::to_string(opcodeLocation.get()));
}

auto JumpsCallsDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  result.insert(result.end(), { 0x18, 0x20, 0x28, 0x30, 0x38 }); // relative
  result.insert(result.end(), { 0xC2, 0xC3, 0xCA, 0xD2, 0xDA }); // absolute
  result.insert(result.end(), { 0xC4, 0xCC, 0xCD, 0xD4, 0xDC }); // calls
  result.insert(result.end(), { 0xC0, 0xC8, 0xC9, 0xD0, 0xD8, 0xD9 }); // returns
  return result;
}

auto JumpsCallsDecoder::type(const OpcodeView& opcode) -> JumpType
{
  switch (opcode.lowerNibble()) {
  case 0x2:
  case 0x3:
  case 0xA:
    return JumpType::Regular;
    break;
  case 0x4:
  case 0xC:
  case 0xD:
    return JumpType::Call;
    break;
  case 0x0:
  case 0x8:
    return JumpType::Return;
    break;
  case 0x9:
    if (opcode.upperNibble() == 0xC) {
      return JumpType::Return;
    } else if (opcode.upperNibble() == 0xD) {
      return JumpType::RetI;
    } else {
      throw std::logic_error("Unhandled opcode: " + std::to_string(opcode.value()));
    }
    break;
  default:
    throw std::logic_error("Unhandled opcode: " + std::to_string(opcode.value()));
  }
}

auto JumpsCallsDecoder::condition(const OpcodeView& opcode) -> Condition
{
  switch (opcode.value()) {
  case 0x18:
  case 0xC3:
  case 0xC9:
  case 0xCD:
  case 0xD9:
    return Condition::None;
    break;
  case 0x20:
  case 0xC0:
  case 0xC2:
  case 0xC4:
    return Condition::NZ;
    break;
  case 0x30:
  case 0xD0:
  case 0xD2:
  case 0xD4:
    return Condition::NC;
    break;
  case 0x28:
  case 0xC8:
  case 0xCA:
  case 0xCC:
    return Condition::Z;
    break;
  case 0x38:
  case 0xD8:
  case 0xDA:
  case 0xDC:
    return Condition::C;
    break;
  default:
    throw std::logic_error("Unhandled");
    break;
  }
}
