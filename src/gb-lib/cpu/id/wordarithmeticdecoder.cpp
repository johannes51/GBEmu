#include "wordarithmeticdecoder.h"

#include <stdexcept>

#include "location/location.h"

auto WordArithmeticDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.getByte() };
  return std::make_unique<WordAluOperation>(determineFunction(opcode), determineRegister(opcode));
}

auto WordArithmeticDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  return { 0x03, 0x13, 0x23, 0x33, 0x09, 0x19, 0x29, 0x39, 0x0B, 0x1B, 0x2B, 0x3B };
}

auto WordArithmeticDecoder::determineFunction(const OpcodeView& opcode) -> WordAluFunction
{
  switch (opcode.lowerNibble()) {
  case 0x3:
    return WordAluFunction::Inc;
    break;
  case 0x9:
    return WordAluFunction::Add;
    break;
  case 0xB:
    return WordAluFunction::Dec;
    break;
  default:
    throw std::invalid_argument { "Unimplemented opcode: " + std::to_string(opcode.value()) };
    break;
  }
}

auto WordArithmeticDecoder::determineRegister(const OpcodeView& opcode) -> WordRegister
{
  switch (opcode.upperNibble()) {
  case 0x0:
    return WordRegister::BC;
    break;
  case 0x1:
    return WordRegister::DE;
    break;
  case 0x2:
    return WordRegister::HL;
    break;
  case 0x3:
    return WordRegister::SP;
    break;
  default:
    throw std::invalid_argument { "Unimplemented opcode: " + std::to_string(opcode.value()) };
    break;
  }
}
