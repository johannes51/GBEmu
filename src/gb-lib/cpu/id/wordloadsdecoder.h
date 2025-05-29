#ifndef WORDLOADSDECODER_H
#define WORDLOADSDECODER_H

#include "instructiondecoder.h"

#include "cpu/id/opcodeview.h"
#include "cpu/registers/registersinterface.h"

class WordLoadsDecoder : public InstructionDecoder {
public:
  WordLoadsDecoder() = default;

  OperationUP decode(const ILocation8& opcodeLocation) const override;
  std::vector<uint8_t> decodedOpcodes() const override;

private:
  static WordRegister selectRegister(const OpcodeView& opcode);
};

#endif // WORDLOADSDECODER_H
