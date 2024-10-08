#ifndef CB_PREFIX_H
#define CB_PREFIX_H

#include "operation.h"

class InstructionDecoder;

class CbPrefix : public Operation {
public:
  explicit CbPrefix(std::unique_ptr<InstructionDecoder>&& decoder);
  DISABLE_COPY_AND_MOVE(CbPrefix)

  void nextOpcode(LocationUP opcode) override;
  bool isComplete() override;
  unsigned cycles() override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  OperationUP realOp_;
  std::unique_ptr<InstructionDecoder> decoder_;
};

#endif // CB_PREFIX_H
