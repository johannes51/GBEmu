#ifndef CONTROLDECODER_H
#define CONTROLDECODER_H

#include "instructiondecoder.h"

class ControlDecoder : public InstructionDecoder {
public:
  ControlDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;

  std::vector<uint8_t> decodedOpcodes() const override;
};

#endif // CONTROLDECODER_H
