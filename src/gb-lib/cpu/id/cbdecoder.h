#ifndef CB_DECODER_H
#define CB_DECODER_H

#include "instructiondecoder.h"

#include "cpu/id/cbopdecoder.h"

class CbDecoder : public InstructionDecoder {
public:
  CbDecoder() = default;

  OperationUP decode(const ILocation8& opcodeLocation) const override;
  std::vector<uint8_t> decodedOpcodes() const override { return { 0xCB }; }
};

#endif // CB_DECODER_H
