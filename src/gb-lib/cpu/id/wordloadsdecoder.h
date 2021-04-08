#ifndef WORDLOADSDECODER_H
#define WORDLOADSDECODER_H

#include "instructiondecoder.h"

#include "cpu/id/opcodeview.h"

enum class WordRegister;

class WordLoadsDecoder : public InstructionDecoder {
public:
  WordLoadsDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;
  std::vector<uint8_t> decodedOpcodes() const override;

private:
  static WordRegister selectRegister(const OpcodeView& opcode);
};

#endif // WORDLOADSDECODER_H
