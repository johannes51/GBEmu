#ifndef CBOPDECODER_H
#define CBDECODER_H

#include "instructiondecoder.h"

enum class CbFunction;
enum class ByteRegister;
class OpcodeView;

class CbOpDecoder : public InstructionDecoder {
public:
  CbOpDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;
  std::vector<uint8_t> decodedOpcodes() const override;

private:
  static CbFunction function(const OpcodeView& opcode);
  static bool indirect(const OpcodeView& opcode);
  static ByteRegister operand(const OpcodeView& opcode);
  static unsigned bit(const OpcodeView& opcode);
};

#endif // CBOPDECODER_H
