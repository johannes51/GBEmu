#include "baseinstructiondecoder.h"

#include <stdexcept>

#include "arithmeticdecoder.h"
#include "cpu/operation/control.h"
#include "cpu/operation/operation.h"
#include "jumpscallsdecoder.h"
#include "loadsdecoder.h"
#include "location/location.h"
#include "opcodeview.h"

BaseInstructionDecoder::BaseInstructionDecoder()
    : decoders_()
{
}

auto BaseInstructionDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  try {
    return decoders_.at(opcodeLocation.get())->decode(opcodeLocation);
  } catch (...) {
    throw std::logic_error("Unimplemented opcode: " + std::to_string(opcodeLocation.get()));
  }
}

void BaseInstructionDecoder::registerDecoder(const InstructionDecoderSP& decoder)
{
  for (const auto& opcode : decoder->decodedOpcodes()) {
    decoders_[opcode] = decoder;
  }
}

auto BaseInstructionDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  for (const auto& decoder : decoders_) {
    result.push_back(decoder.first);
  }
  return result;
}
