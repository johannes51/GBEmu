#include "stackopdecoder.h"

#include <stdexcept>

#include "cpu/operation/stackop.h"
#include "location/location.h"

auto StackOpDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  OpcodeView opcode { opcodeLocation.get() };
  auto isPush = opcode.lowerNibble() == 0x5;
  return std::make_unique<StackOp>(isPush, selectRegister(opcode));
}

auto StackOpDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  return { 0xC1, 0xD1, 0xE1, 0xF1, 0xC5, 0xD5, 0xE5, 0xF5 };
}

auto StackOpDecoder::selectRegister(const OpcodeView& opcode) -> WordRegister
{
  switch (opcode.upperNibble()) {
  case 0xC:
    return WordRegister::BC;
    break;
  case 0xD:
    return WordRegister::DE;
    break;
  case 0xE:
    return WordRegister::HL;
    break;
  case 0xF:
    return WordRegister::AF;
    break;
  default:
    throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
    break;
  }
}
