#ifndef BYTELOADSDECODER_H
#define BYTELOADSDECODER_H

#include "instructiondecoder.h"

class ByteLoadsDecoder : public InstructionDecoder {
public:
  ByteLoadsDecoder() = default;

  OperationUP decode(const ILocation8& opcodeLocation) const override;

  std::vector<uint8_t> decodedOpcodes() const override;
};

#endif // BYTELOADSDECODER_H
