#ifndef UNIMPLMENTEDDECODER_H
#define UNIMPLMENTEDDECODER_H

#include "instructiondecoder.h"

class UnimplementedDecoder : public InstructionDecoder {
public:
  UnimplementedDecoder() = default;

  OperationUP decode(const Location8& opcodeLocation) const override;
  std::vector<uint8_t> decodedOpcodes() const override;

private:
  static const std::vector<uint8_t> decodedOpcodes_;
};

#endif // UNIMPLMENTEDDECODER_H
