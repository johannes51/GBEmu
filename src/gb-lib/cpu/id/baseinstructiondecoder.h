#ifndef BASEINSTRUCTIONDECODER_H
#define BASEINSTRUCTIONDECODER_H

#include <unordered_map>

#include "instructiondecoder.h"

class BaseInstructionDecoder : public InstructionDecoder {
public:
  BaseInstructionDecoder();

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;

  void registerOpcode(const uint8_t& opcode, InstructionDecoderSP decoder);

private:
  std::unordered_map<uint8_t, InstructionDecoderSP> decoders_;
};

#endif // BASEINSTRUCTIONDECODER_H
