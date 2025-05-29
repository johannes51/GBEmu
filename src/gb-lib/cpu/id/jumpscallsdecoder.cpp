#include "jumpscallsdecoder.h"

#include <stdexcept>

#include "cpu/operation/jump.h"
#include "mem/rest/variablelocation.h"

auto JumpsCallsDecoder::decode(const ILocation8& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.get() };
  if (opcode.upperNibble() <= 0x3U) {
    return std::make_unique<Jump>(JumpType::Regular, TargetType::Relative, condition(opcode));
  } else {
    if (opcode.value() == 0xE9U) {
      return std::make_unique<Jump>(JumpType::Indirect, TargetType::Absolute, Condition::None);
    } else {
      auto result = std::make_unique<Jump>(type(opcode), TargetType::Absolute, condition(opcode));
      if (opcode.lowerNibble() == 0x7U || opcode.lowerNibble() == 0xFU) {
        feedResetOpcode(*result, opcode);
      }
      return result;
    }
  }
  throw std::logic_error("Unhandled opcode: " + std::to_string(opcodeLocation.get()));
}

auto JumpsCallsDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  result.insert(result.end(), { 0x18U, 0x20U, 0x28U, 0x30U, 0x38U }); // relative
  result.insert(result.end(), { 0xC2U, 0xC3U, 0xCAU, 0xD2U, 0xDAU, 0xE9U }); // absolute
  result.insert(result.end(), { 0xC4U, 0xCCU, 0xCDU, 0xD4U, 0xDCU }); // calls
  result.insert(result.end(), { 0xC0U, 0xC8U, 0xC9U, 0xD0U, 0xD8U, 0xD9U }); // returns
  result.insert(result.end(), { 0xC7U, 0xD7U, 0xE7U, 0xF7U, 0xCFU, 0xDFU, 0xEFU, 0xFFU }); // resets
  return result;
}

auto JumpsCallsDecoder::type(const OpcodeView& opcode) -> JumpType
{
  switch (opcode.lowerNibble()) {
  case 0x2U:
  case 0x3U:
  case 0xAU:
    return JumpType::Regular;
  case 0x4U:
  case 0xCU:
  case 0xDU:
    return JumpType::Call;
  case 0x0U:
  case 0x8U:
    return JumpType::Return;
  case 0x9U:
    return (opcode.upperNibble() == 0xCU) ? JumpType::Return : JumpType::RetI;
  case 0x7U:
  case 0xFU:
    return JumpType::Reset;
  default:
    throw std::logic_error("Unhandled opcode: " + std::to_string(opcode.value()));
  }
}

auto JumpsCallsDecoder::condition(const OpcodeView& opcode) -> Condition
{
  switch (opcode.value()) {
  case 0x18U:
  case 0xC3U:
  case 0xC9U:
  case 0xCDU:
  case 0xD9U:
  case 0xE9U:
  case 0xC7U:
  case 0xD7U:
  case 0xE7U:
  case 0xF7U:
  case 0xCFU:
  case 0xDFU:
  case 0xEFU:
  case 0xFFU:
    return Condition::None;
  case 0x20U:
  case 0xC0U:
  case 0xC2U:
  case 0xC4U:
    return Condition::NZ;
  case 0x30U:
  case 0xD0U:
  case 0xD2U:
  case 0xD4U:
    return Condition::NC;
  case 0x28U:
  case 0xC8U:
  case 0xCAU:
  case 0xCCU:
    return Condition::Z;
  case 0x38U:
  case 0xD8U:
  case 0xDAU:
  case 0xDCU:
    return Condition::C;
  default:
    throw std::logic_error("Unhandled");
  }
}

void JumpsCallsDecoder::feedResetOpcode(Operation& op, OpcodeView opcode)
{
  uint8_t lower = 0x00U;
  switch (opcode.value()) {
  default:
  case 0xC7U:
    lower = 0x00U;
    break;
  case 0xD7U:
    lower = 0x10U;
    break;
  case 0xE7U:
    lower = 0x20U;
    break;
  case 0xF7U:
    lower = 0x30U;
    break;
  case 0xCFU:
    lower = 0x08U;
    break;
  case 0xDFU:
    lower = 0x18U;
    break;
  case 0xEFU:
    lower = 0x28U;
    break;
  case 0xFFU:
    lower = 0x38U;
    break;
  }
  op.nextOpcode(variableLocation(lower));
  op.nextOpcode(variableLocation(uint8_t { 0U }));
}
