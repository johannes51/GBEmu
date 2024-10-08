#ifndef CB_DECODER_H
#define CB_DECODER_H

#include "instructiondecoder.h"

#include "cpu/id/cbopdecoder.h"

class CbDecoder : public InstructionDecoder {
public:
  CbDecoder() = default;

  OperationUP decode(const Location& opcodeLocation) const override;
  std::vector<uint8_t> decodedOpcodes() const override { return { 0xCB }; }
};

#endif // CB_DECODER_H
