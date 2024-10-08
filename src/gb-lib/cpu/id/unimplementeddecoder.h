#ifndef UNIMPLMENTEDDECODER_H
#define UNIMPLMENTEDDECODER_H

#include "instructiondecoder.h"

class UnimplmentedDecoder : public InstructionDecoder {
public:
  UnimplmentedDecoder() = default;

  OperationUP decode(const Location& opcodeLocation) const override;
  std::vector<uint8_t> decodedOpcodes() const override;

private:
  static const std::vector<uint8_t> decodedOpcodes_;
};

#endif // UNIMPLMENTEDDECODER_H
