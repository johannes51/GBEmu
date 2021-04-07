#ifndef STACKOPDECODER_H
#define STACKOPDECODER_H

#include "instructiondecoder.h"

#include "cpu/id/opcodeview.h"

enum class WordRegister;

class StackOpDecoder : public InstructionDecoder {
public:
  StackOpDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;
  std::vector<uint8_t> decodedOpcodes() const override;

private:
  static WordRegister selectRegister(const OpcodeView& opcode);
};

#endif // STACKOPDECODER_H
