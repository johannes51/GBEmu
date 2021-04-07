#ifndef BYTEARITHMETICDECODER_H
#define BYTEARITHMETICDECODER_H

#include "instructiondecoder.h"

class ByteArithmeticDecoder : public InstructionDecoder {
public:
  ByteArithmeticDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;
  std::vector<uint8_t> decodedOpcodes() const override;
};

#endif // BYTEARITHMETICDECODER_H
