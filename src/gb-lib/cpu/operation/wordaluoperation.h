#ifndef WORDALUOPERATION_H
#define WORDALUOPERATION_H

#include "singleop.h"

#include "cpu/registersinterface.h"

namespace ops {
struct OpResult;
}

enum class WordAluFunction { Inc, Add, Dec };

class WordAluOperation : public SingleOp<2> {
public:
  WordAluOperation(WordAluFunction function, WordRegister targetRegister);

  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  WordAluFunction function_;
  WordRegister register_;
};

#endif // WORDALUOPERATION_H
