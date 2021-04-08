#ifndef BYTELOADSDECODER_H
#define BYTELOADSDECODER_H

#include "instructiondecoder.h"

class ByteLoadsDecoder : public InstructionDecoder {
public:
  ByteLoadsDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;

  std::vector<uint8_t> decodedOpcodes() const override;
};

#endif // BYTELOADSDECODER_H
