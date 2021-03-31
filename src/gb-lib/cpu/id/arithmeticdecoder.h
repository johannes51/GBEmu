#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "instructiondecoder.h"

class ArithmeticDecoder : public InstructionDecoder {
  static constexpr uint8_t JumpDirect = 0xC3;
  static constexpr uint8_t JumpRelative = 0x18;

public:
  ArithmeticDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;
  std::vector<uint8_t> decodedOpcodes() const override;
};

#endif // ARITHMETIC_H
