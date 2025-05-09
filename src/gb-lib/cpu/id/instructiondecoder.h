#ifndef INSTRUCTIONDECODER_H
#define INSTRUCTIONDECODER_H

#include <vector>

#include "cpu/cpu_defines.h"
#include "location/location8.h"

class InstructionDecoder {
public:
  virtual ~InstructionDecoder() = default;

  virtual OperationUP decode(const Location8& opcodeLocation) const = 0;

  virtual std::vector<uint8_t> decodedOpcodes() const = 0;

protected:
  InstructionDecoder() = default;
};

using InstructionDecoderUP = std::unique_ptr<InstructionDecoder>;
using InstructionDecoderSP = std::shared_ptr<InstructionDecoder>;

#endif // INSTRUCTIONDECODER_H
