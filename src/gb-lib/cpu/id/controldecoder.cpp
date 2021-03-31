#include "controldecoder.h"

#include <stdexcept>

#include "cpu/operation/control.h"
#include "cpu/operation/operation.h"
#include "location/location.h"

auto ControlDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  switch (opcodeLocation.get()) {
  case 0x00:
    return std::make_unique<Control>(ControlOp::Nop);
    break;
  case 0xFB:
    return std::make_unique<Control>(ControlOp::EI);
    break;
  case 0xF3:
    return std::make_unique<Control>(ControlOp::DI);
    break;
  default:
    throw std::logic_error { "Cannot decode instruction: " + std::to_string(opcodeLocation.get()) };
    break;
  }
}

auto ControlDecoder::decodedOpcodes() const -> std::vector<uint8_t> { return { 0x00, 0xF3, 0xFB }; }
