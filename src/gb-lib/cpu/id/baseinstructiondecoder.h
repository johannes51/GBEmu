#ifndef BASEINSTRUCTIONDECODER_H
#define BASEINSTRUCTIONDECODER_H

#include <unordered_map>

#include "instructiondecoder.h"

class BaseInstructionDecoder : public InstructionDecoder {
public:
  BaseInstructionDecoder();

  OperationUP decode(const ILocation8& opcodeLocation) const override;

  void registerDecoder(const InstructionDecoderSP& decoder);

  std::vector<uint8_t> decodedOpcodes() const override;

private:
  std::unordered_map<uint8_t, InstructionDecoderSP> decoders_;
};

#endif // BASEINSTRUCTIONDECODER_H
