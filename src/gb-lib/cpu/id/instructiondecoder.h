#ifndef INSTRUCTIONDECODER_H
#define INSTRUCTIONDECODER_H

#include "cpu/cpu_defines.h"
#include "location/location_defines.h"

class InstructionDecoder {
public:
  virtual ~InstructionDecoder() = default;

  virtual OperationUP decode(const Location<uint8_t>& opcodeLocation) = 0;

protected:
  InstructionDecoder() = default;
};

using InstructionDecoderUP = std::unique_ptr<InstructionDecoder>;
using InstructionDecoderSP = std::shared_ptr<InstructionDecoder>;

#endif // INSTRUCTIONDECODER_H
