#ifndef CONTROLDECODER_H
#define CONTROLDECODER_H

#include "instructiondecoder.h"

class ControlDecoder : public InstructionDecoder {
public:
  ControlDecoder() = default;

  OperationUP decode(const ILocation8& opcodeLocation) const override;

  std::vector<uint8_t> decodedOpcodes() const override;
};

#endif // CONTROLDECODER_H
