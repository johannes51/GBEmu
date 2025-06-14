#include "cbdecoder.h"

#include <stdexcept>

#include "cpu/operation/cbprefix.h"
#include "mem/ilocation8.h"
#include "opcodeview.h"

auto CbDecoder::decode(const ILocation8& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.get() };
  if (opcode.value() == 0xCBU) {
    return std::make_unique<CbPrefix>(std::make_unique<CbOpDecoder>());
  } else {
    throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
  }
}
