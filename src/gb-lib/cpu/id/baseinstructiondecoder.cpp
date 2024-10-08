#include "baseinstructiondecoder.h"

#include <stdexcept>

#include "cpu/operation/operation.h"
#include "location/location.h"

BaseInstructionDecoder::BaseInstructionDecoder()
    : decoders_()
{
}

auto BaseInstructionDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  InstructionDecoder* decoder = nullptr;
  try {
    decoder = decoders_.at(opcodeLocation.getByte()).get();
  } catch (...) {
    throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcodeLocation.getByte()));
  }
  return decoder->decode(opcodeLocation);
}

void BaseInstructionDecoder::registerDecoder(const InstructionDecoderSP& decoder)
{
  for (const auto& opcode : decoder->decodedOpcodes()) {
    if (decoders_.find(opcode) != decoders_.end()) {
      throw std::logic_error("Opcode already registered: " + std::to_string(opcode));
    }
    decoders_[opcode] = decoder;
  }
}

auto BaseInstructionDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  for (const auto& decoder : decoders_) {
    result.push_back(decoder.first); // NOLINT(performance-inefficient-vector-operation)
  }
  return result;
}
