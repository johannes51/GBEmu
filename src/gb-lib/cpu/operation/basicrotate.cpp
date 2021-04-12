#include "basicrotate.h"

#include "cpu/flagsview.h"
#include "cpu/registersinterface.h"
#include "ops/shiftrotatebitwise.h"
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
    ops::rr(reg);
    if (throughCarry_) {
      const auto oldCarry = registers.getFlags().carry();
      auto value = reg.get();
      if (hlp::checkBit(value, hlp::MinBit)) {
        registers.getFlags().setCarry();
      } else {
        registers.getFlags().clearCarry();
      }
      if (oldCarry) {
        hlp::setBit(value, hlp::MaxBit);
      } else {
        hlp::clearBit(value, hlp::MaxBit);
      }
    }
  } else /*if (direction_ == RotateDirection::Left)*/ {
    ops::rl(reg);
    if (throughCarry_) {
      const auto oldCarry = registers.getFlags().carry();
      auto value = reg.get();
      if (hlp::checkBit(value, hlp::MaxBit)) {
        registers.getFlags().setCarry();
      } else {
        registers.getFlags().clearCarry();
      }
      if (oldCarry) {
        hlp::setBit(value, hlp::MinBit);
      } else {
        hlp::clearBit(value, hlp::MinBit);
      }
    }
  }
}
