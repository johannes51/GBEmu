#ifndef WORDALUOPERATION_H
#define WORDALUOPERATION_H

#include "singleop.h"

#include "cpu/registersinterface.h"

namespace ops {
struct OpResult;
}

enum class WordAluFunction { Inc, Add, Dec };

class WordAluOperation : public SingleOp {
public:
  WordAluOperation(WordAluFunction function, WordRegister targetRegister);

  unsigned int cycles(const RegistersInterface& registers) override
  {
    (void)registers;
    return 2;
  }
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

private:
  static void apply(FlagsView& flags, const ops::OpResult& result);

  WordAluFunction function_;
  WordRegister register_;
};

#endif // WORDALUOPERATION_H
