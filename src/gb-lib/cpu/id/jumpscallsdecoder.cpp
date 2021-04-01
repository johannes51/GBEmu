#include "jumpscallsdecoder.h"

#include <stdexcept>

#include "cpu/id/opcodeview.h"
#include "cpu/operation/jump.h"

auto condition(const OpcodeView& opcode) -> Condition
{
  switch (opcode.value()) {
  case 0x18:
  case 0xC3:
    return Condition::None;
    break;
  case 0x20:
  case 0xC2:
    return Condition::NZ;
    break;
  case 0x30:
  case 0xD2:
    return Condition::NC;
    break;
  case 0x28:
  case 0xCA:
    return Condition::Z;
    break;
  case 0x38:
  case 0xDA:
    return Condition::C;
    break;
  default:
    throw std::logic_error("Unhandled");
    break;
  }
}

auto JumpsCallsDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  OpcodeView opcode { opcodeLocation.get() };
  if (opcode.upperNibble() <= 0x3) {
    return std::make_unique<Jump>(JumpType::Relative, condition(opcode));
  } else {
    return std::make_unique<Jump>(JumpType::Absolute, condition(opcode));
  }
  throw std::logic_error("Unhandled opcode: " + std::to_string(opcodeLocation.get()));
}

auto JumpsCallsDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  result.insert(result.end(), { 0x18, 0x20, 0x28, 0x30, 0x38 }); // relative
  result.insert(result.end(), { 0xC2, 0xC3, 0xCA, 0xD2, 0xDA }); // absolute
  return result;
}
