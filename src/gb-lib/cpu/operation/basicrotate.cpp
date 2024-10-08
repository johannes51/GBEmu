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
  if (direction_ == RotateDirection::Right) {
    if (throughCarry_) {
      ops::rr(*reg, registers.getFlags().carry());
    } else {
      ops::rrc(*reg);
    }
  } else /*if (direction_ == RotateDirection::Left)*/ {
    if (throughCarry_) {
      ops::rl(*reg, registers.getFlags().carry());
    } else {
      ops::rlc(*reg);
    }
  }
}
