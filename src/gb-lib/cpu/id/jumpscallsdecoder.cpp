#include "jumpscallsdecoder.h"

#include <stdexcept>

#include "cpu/operation/jump.h"

auto JumpsCallsDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  if (opcodeLocation.get() != JumpDirect) {
    throw std::logic_error("Unhandled opcode: " + std::to_string(opcodeLocation.get()));
  }
  return std::make_unique<Jump>(JumpType::Direct);
}

auto JumpsCallsDecoder::decodedOpcodes() const -> std::vector<uint8_t> { return { JumpDirect }; }
