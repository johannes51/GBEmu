#ifndef JUMPS_CALLS_H
#define JUMPS_CALLS_H

#include "instructiondecoder.h"

class JumpsCallsDecoder : public InstructionDecoder {
  static constexpr uint8_t JumpDirect = 0xC3;
  static constexpr uint8_t JumpRelative = 0x18;

public:
  JumpsCallsDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;
  std::vector<uint8_t> decodedOpcodes() const override;
};

#endif // JUMPS_CALLS_H
