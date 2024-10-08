#include "miscarithmeticdecoder.h"

#include <algorithm>
#include <stdexcept>

#include "../operation/miscarithmetic.h"
#include "location/location.h"
#include "opcodeview.h"

const std::vector<uint8_t> MiscArithmeticDecoder::decodedOpcodes_ = { 0x27, 0x37, 0x2F, 0x3F };

auto MiscArithmeticDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.getByte() };
  if (std::find(std::begin(decodedOpcodes_), std::end(decodedOpcodes_), opcode.value()) == std::end(decodedOpcodes_)) {
    throw std::logic_error { "Unimplemented opcode: " + std::to_string(opcodeLocation.getByte()) };
  }
  return std::make_unique<MiscArithmetic>(decodeFunction(opcode.value()));
}

auto MiscArithmeticDecoder::decodedOpcodes() const -> std::vector<uint8_t> { return decodedOpcodes_; }

auto MiscArithmeticDecoder::decodeFunction(uint8_t opcode) -> MiscArithmeticFunction
{
  switch (opcode) {
  case 0x27:
    return MiscArithmeticFunction::DecimalAdjustA;
    break;
  case 0x37:
    return MiscArithmeticFunction::SetCarry;
    break;
  case 0x2F:
    return MiscArithmeticFunction::ComplementA;
    break;
  case 0x3F:
    return MiscArithmeticFunction::ComplementCarry;
    break;
  default:
    throw std::logic_error { "Unimplemented opcode: " + std::to_string(opcode) };
    break;
  }
}
