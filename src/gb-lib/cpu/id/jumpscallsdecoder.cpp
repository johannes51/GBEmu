#include "jumpscallsdecoder.h"

#include <stdexcept>

#include "cpu/operation/jump.h"
#include "location/variablebyte.h"
#include "location/zerobyte.h"

auto JumpsCallsDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  OpcodeView opcode { opcodeLocation.get() };
  if (opcode.upperNibble() <= 0x3) {
    return std::make_unique<Jump>(JumpType::Regular, TargetType::Relative, condition(opcode));
  } else {
    if (opcode.value() == 0xE9) {
      return std::make_unique<Jump>(JumpType::Indirect, TargetType::Absolute, Condition::None);
    } else {
      auto result = std::make_unique<Jump>(type(opcode), TargetType::Absolute, condition(opcode));
      if (opcode.lowerNibble() == 0x7 || opcode.lowerNibble() == 0xF) {
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
  result.insert(result.end(), { 0x18, 0x20, 0x28, 0x30, 0x38 }); // relative
  result.insert(result.end(), { 0xC2, 0xC3, 0xCA, 0xD2, 0xDA, 0xE9 }); // absolute
  result.insert(result.end(), { 0xC4, 0xCC, 0xCD, 0xD4, 0xDC }); // calls
  result.insert(result.end(), { 0xC0, 0xC8, 0xC9, 0xD0, 0xD8, 0xD9 }); // returns
  result.insert(result.end(), { 0xC7, 0xD7, 0xE7, 0xF7, 0xCF, 0xDF, 0xEF, 0xFF }); // resets
  return result;
}

auto JumpsCallsDecoder::type(const OpcodeView& opcode) -> JumpType
{
  switch (opcode.lowerNibble()) {
  case 0x2:
  case 0x3:
  case 0xA:
    return JumpType::Regular;
  case 0x4:
  case 0xC:
  case 0xD:
    return JumpType::Call;
  case 0x0:
  case 0x8:
    return JumpType::Return;
  case 0x9:
    return (opcode.upperNibble() == 0xC) ? JumpType::Return : JumpType::RetI;
  case 0x7:
  case 0xF:
    return JumpType::Reset;
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
  case 0xE9:
  case 0xC7:
  case 0xD7:
  case 0xE7:
  case 0xF7:
  case 0xCF:
  case 0xDF:
  case 0xEF:
  case 0xFF:
    return Condition::None;
  case 0x20:
  case 0xC0:
  case 0xC2:
  case 0xC4:
    return Condition::NZ;
  case 0x30:
  case 0xD0:
  case 0xD2:
  case 0xD4:
    return Condition::NC;
  case 0x28:
  case 0xC8:
  case 0xCA:
  case 0xCC:
    return Condition::Z;
  case 0x38:
  case 0xD8:
  case 0xDA:
  case 0xDC:
    return Condition::C;
  default:
    throw std::logic_error("Unhandled");
  }
}

void JumpsCallsDecoder::feedResetOpcode(Operation& op, OpcodeView opcode)
{
  uint8_t lower = 0x00;
  switch (opcode.value()) {
  case 0xC7:
    lower = 0x00;
    break;
  case 0xD7:
    lower = 0x10;
    break;
  case 0xE7:
    lower = 0x20;
    break;
  case 0xF7:
    lower = 0x30;
    break;
  case 0xCF:
    lower = 0x08;
    break;
  case 0xDF:
    lower = 0x18;
    break;
  case 0xEF:
    lower = 0x28;
    break;
  case 0xFF:
    lower = 0x38;
    break;
  default:
    break;
  }
  op.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(lower)));
  op.nextOpcode(Location<uint8_t>::generate(std::make_unique<ZeroByte>()));
}
