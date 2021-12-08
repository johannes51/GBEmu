#ifndef CBDECODER_H
#define CBDECODER_H

#include "instructiondecoder.h"

class CbDecoder : public InstructionDecoder {
public:
  CbDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;
  std::vector<uint8_t> decodedOpcodes() const override { return { 0xCB }; }
};

#endif // CBDECODER_H
