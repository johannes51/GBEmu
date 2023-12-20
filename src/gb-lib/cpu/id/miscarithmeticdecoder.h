#ifndef MISCARITHMETICDECODER_H
#define MISCARITHMETICDECODER_H

#include "instructiondecoder.h"

enum class MiscArithmeticFunction;

class MiscArithmeticDecoder : public InstructionDecoder {
public:
  MiscArithmeticDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;
  std::vector<uint8_t> decodedOpcodes() const override;

private:
  static MiscArithmeticFunction decodeFunction(uint8_t opcode);

  static const std::vector<uint8_t> decodedOpcodes_;
};

#endif // MISCARITHMETICDECODER_H
