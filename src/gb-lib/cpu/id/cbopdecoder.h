#ifndef CBOP_DECODER_H
#define CBOP_DECODER_H

#include "instructiondecoder.h"

enum class CbFunction;
enum class ByteRegister;
class OpcodeView;

class CbOpDecoder : public InstructionDecoder {
public:
  CbOpDecoder() = default;

  OperationUP decode(const ILocation8& opcodeLocation) const override;
  std::vector<uint8_t> decodedOpcodes() const override { return {}; }
};

#endif // CBOP_DECODER_H
