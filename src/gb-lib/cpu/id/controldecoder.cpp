#include "controldecoder.h"

#include <stdexcept>

#include "cpu/operation/control.h"
#include "cpu/operation/operation.h"
#include "location/location.h"

auto ControlDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  switch (opcodeLocation.getByte()) {
  case 0x00U:
    return std::make_unique<Control>(ControlOp::Nop);
    break;
  case 0x10U:
    return std::make_unique<Control>(ControlOp::Stop);
    break;
  case 0x76U:
    return std::make_unique<Control>(ControlOp::Halt);
    break;
  case 0xFBU:
    return std::make_unique<Control>(ControlOp::EI);
    break;
  case 0xF3U:
    return std::make_unique<Control>(ControlOp::DI);
    break;
  default:
    throw std::logic_error { "Cannot decode instruction: " + std::to_string(opcodeLocation.getByte()) };
    break;
  }
}

auto ControlDecoder::decodedOpcodes() const -> std::vector<uint8_t> { return { 0x00U, 0x10U, 0x76U, 0xF3U, 0xFBU }; }
