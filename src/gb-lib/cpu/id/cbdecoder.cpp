#include "cbdecoder.h"

#include <stdexcept>

#include "cpu/operation/cbprefix.h"
#include "location/location.h"
#include "opcodeview.h"

auto CbDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.getByte() };
  if (opcode.value() == 0xCB) {
    return std::make_unique<CbPrefix>(std::make_unique<CbOpDecoder>());
  } else {
    throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
  }
}
