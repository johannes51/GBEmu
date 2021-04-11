#ifndef CBPREFIX_H
#define CBPREFIX_H

#include "operation.h"

class InstructionDecoder;

class CbPrefix : public Operation {
public:
  explicit CbPrefix(InstructionDecoder* decoder);
  DISABLE_COPY_AND_MOVE(CbPrefix)

  void nextOpcode(Location<uint8_t> opcode) override;
  bool isComplete() override;
  unsigned cycles(const RegistersInterface& registers) override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  OperationUP realOp_;
  InstructionDecoder* decoder_;
};

#endif // CBPREFIX_H
