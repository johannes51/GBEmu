#ifndef WORDARITHMETICDECODER_H
#define WORDARITHMETICDECODER_H

#include "instructiondecoder.h"

#include "cpu/id/opcodeview.h"
#include "cpu/operation/wordaluoperation.h"
#include "cpu/registersinterface.h"

class WordArithmeticDecoder : public InstructionDecoder {
public:
  WordArithmeticDecoder() = default;

  OperationUP decode(const Location8& opcodeLocation) const override;
  std::vector<uint8_t> decodedOpcodes() const override;

private:
  static WordAluFunction determineFunction(const OpcodeView& opcode);
  static WordRegister determineRegister(const OpcodeView& opcode);
};

#endif // WORDARITHMETICDECODER_H
