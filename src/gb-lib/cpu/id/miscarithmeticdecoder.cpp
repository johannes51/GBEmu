#include "miscarithmeticdecoder.h"

#include <stdexcept>

#include "../operation/miscarithmetic.h"
#include "mem/ilocation8.h"
#include "opcodeview.h"

const std::vector<uint8_t> MiscArithmeticDecoder::decodedOpcodes_ = { 0x27U, 0x37U, 0x2FU, 0x3FU };

auto MiscArithmeticDecoder::decode(const ILocation8& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.get() };
  return std::make_unique<MiscArithmetic>(decodeFunction(opcode.value()));
}

auto MiscArithmeticDecoder::decodedOpcodes() const -> std::vector<uint8_t> { return decodedOpcodes_; }

auto MiscArithmeticDecoder::decodeFunction(uint8_t opcode) -> MiscArithmeticFunction
{
  switch (opcode) {
  case 0x27U:
    return MiscArithmeticFunction::DecimalAdjustA;
    break;
  case 0x37U:
    return MiscArithmeticFunction::SetCarry;
    break;
  case 0x2FU:
    return MiscArithmeticFunction::ComplementA;
    break;
  case 0x3FU:
    return MiscArithmeticFunction::ComplementCarry;
    break;
  default:
    throw std::logic_error { "Unimplemented opcode: " + std::to_string(opcode) };
    break;
  }
}
