#ifndef LOADS_H
#define LOADS_H

#include "instructiondecoder.h"

class LoadsDecoder : public InstructionDecoder {
public:
  LoadsDecoder() = default;

  OperationUP decode(const Location<uint8_t>& opcodeLocation) override;

  std::vector<uint8_t> decodedOpcodes() const override;
};

#endif // LOADS_H
