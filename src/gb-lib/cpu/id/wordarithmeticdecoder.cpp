#include "wordarithmeticdecoder.h"

#include <stdexcept>

#include "mem/location8.h"

auto WordArithmeticDecoder::decode(const Location8& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.get() };
  return std::make_unique<WordAluOperation>(determineFunction(opcode), determineRegister(opcode));
}

auto WordArithmeticDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  return { 0x03U, 0x13U, 0x23U, 0x33U, 0x09U, 0x19U, 0x29U, 0x39U, 0x0BU, 0x1BU, 0x2BU, 0x3BU };
}

auto WordArithmeticDecoder::determineFunction(const OpcodeView& opcode) -> WordAluFunction
{
  switch (opcode.lowerNibble()) {
  case 0x3U:
    return WordAluFunction::Inc;
    break;
  case 0x9U:
    return WordAluFunction::Add;
    break;
  case 0xBU:
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
  case 0x0U:
    return WordRegister::BC;
    break;
  case 0x1U:
    return WordRegister::DE;
    break;
  case 0x2U:
    return WordRegister::HL;
    break;
  case 0x3U:
    return WordRegister::SP;
    break;
  default:
    throw std::invalid_argument { "Unimplemented opcode: " + std::to_string(opcode.value()) };
    break;
  }
}
