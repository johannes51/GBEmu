#include "basicrotate.h"

#include "cpu/flagsview.h"
#include "cpu/registersinterface.h"
#include "ops/shiftrotate.h"
#include "util/helpers.h"

BasicRotate::BasicRotate(const RotateDirection& direction, bool throughCarry)
    : direction_(direction)
    , throughCarry_(throughCarry)
{
}

void BasicRotate::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  auto reg = registers.get(ByteRegister::A);
  auto result = ops::OpResult { .z = ops::FlagResult::NoChange,
    .n = ops::FlagResult::NoChange,
    .h = ops::FlagResult::NoChange,
    .c = ops::FlagResult::NoChange };
  if (direction_ == RotateDirection::Right) {
    if (throughCarry_) {
      result = ops::rr(reg, registers.getFlags().carry());
    } else {
      result = ops::rr(reg);
    }
  } else /*if (direction_ == RotateDirection::Left)*/ {
    if (throughCarry_) {
      result = ops::rl(reg, registers.getFlags().carry());
    } else {
      result = ops::rl(reg);
    }
  }
  result.z = ops::FlagResult::Reset;
  result.n = ops::FlagResult::Reset;
  result.h = ops::FlagResult::Reset;
  apply(registers.getFlags(), result);
}
