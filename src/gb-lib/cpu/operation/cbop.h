#ifndef CBOP_H
#define CBOP_H

#include "singleop.h"

#include "../registers/registersinterface.h"

class CbOp : public SingleOp<0> {
public:
  enum class CbFunction {
    RotateRight,
    RotateRightCiruclar,
    RotateLeft,
    RotateLeftCircular,
    ShiftRightArithmetic,
    ShiftLeftArithmetic,
    ShiftRightLogic,
    Swap,
    Bit,
    Set,
    Reset
  };

  explicit CbOp(CbFunction function, ByteRegister operand, bool indirect = false);

  bool isComplete() override;

  unsigned cycles() override;
  void execute(RegistersInterface& registers, IMemoryWordView& memory) override;

  void setAffectedBit(uint8_t value);
  static constexpr uint8_t MaxBit = 7;

private:
  static constexpr uint8_t INVALID_BIT = 8U;

  CbFunction function_;
  ByteRegister operand_;
  bool indirect_;
  unsigned affectedBit_;
};

#endif // CBOP_H
