#ifndef JUMPS_CALLS_H
#define JUMPS_CALLS_H

#include "instructiondecoder.h"

#include "cpu/id/opcodeview.h"

enum class JumpType;
enum class Condition;

class JumpsCallsDecoder : public InstructionDecoder {
public:
  JumpsCallsDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;
  std::vector<uint8_t> decodedOpcodes() const override;

private:
  static JumpType type(const OpcodeView& opcode);
  static Condition condition(const OpcodeView& opcode);
  static void feedResetOpcode(Operation& op, OpcodeView opcode);
};

#endif // JUMPS_CALLS_H
