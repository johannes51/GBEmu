#ifndef INSTRUCTIONDECODER_H
#define INSTRUCTIONDECODER_H

#include <vector>

#include "../operation/operation.h"
#include "mem/ilocation8.h"

class InstructionDecoder {
public:
  virtual ~InstructionDecoder() = default;

  virtual OperationUP decode(const ILocation8& opcodeLocation) const = 0;

  virtual std::vector<uint8_t> decodedOpcodes() const = 0;

protected:
  InstructionDecoder() = default;
};

using InstructionDecoderUP = std::unique_ptr<InstructionDecoder>;
using InstructionDecoderSP = std::shared_ptr<InstructionDecoder>;

#endif // INSTRUCTIONDECODER_H
