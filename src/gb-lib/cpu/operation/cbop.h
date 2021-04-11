#ifndef CBOP_H
#define CBOP_H

#include "singleop.h"

#include "cpu/registersinterface.h"

enum class CbFunction {
  RotateRight,
  RotateRightCarry,
  RotateLeft,
  RotateLeftCarry,
  ShiftRightArit,
  ShiftLeftArit,
  ShiftRightLogic,
  Swap,
  Bit,
  Set,
  Reset
};

class CbOp : public SingleOp<0> {
public:
  CbOp(CbFunction function, bool indirect, ByteRegister operand = ByteRegister::None);

  bool isComplete() override { return true; }
  unsigned cycles(const RegistersInterface& registers) override;
  void execute(RegistersInterface& registers, IMemoryView& memory) override;

  void setAffectedBit(uint8_t value);
  static constexpr uint8_t MaxBit = 7;

private:
  Location<uint8_t> selectOperand(RegistersInterface& registers, IMemoryView& memory);

  CbFunction function_;
  bool indirect_;
  ByteRegister operand_;
  unsigned affectedBit_;
};

#endif // CBOP_H
