#ifndef BASICROTATEDECODER_H
#define BASICROTATEDECODER_H

#include "instructiondecoder.h"

class BasicRotateDecoder : public InstructionDecoder {
public:
  BasicRotateDecoder() = default;

  OperationUP decode(const ILocation8& opcodeLocation) const override;
  std::vector<uint8_t> decodedOpcodes() const override;
};

#endif // BASICROTATEDECODER_H
