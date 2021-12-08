#include "cbdecoder.h"

#include <stdexcept>

#include "cpu/id/cbopdecoder.h"
#include "cpu/operation/cbprefix.h"
#include "location/location.h"
#include "opcodeview.h"

auto CbDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  OpcodeView opcode { opcodeLocation.get() };
  if (opcode.value() == 0xCB) {
    return std::make_unique<CbPrefix>(std::make_unique<CbOpDecoder>());
  } else {
    throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
  }
}
