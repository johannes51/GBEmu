#include "cbop.h"

#include <stdexcept>

#include "cpu/id/cbopdecoder.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "ops/bitmanip.h"
#include "ops/shiftrotate.h"
#include "util/helpers.h"

CbOp::CbOp(CbFunction function, ByteRegister operand, bool indirect)
    : function_(function)
    , operand_(operand)
    , indirect_(indirect)
    , affectedBit_(INVALID_BIT)
{
}

auto CbOp::isComplete() -> bool
{
  return (function_ != CbFunction::Bit && function_ != CbFunction::Set && function_ != CbFunction::Reset)
      || (affectedBit_ < INVALID_BIT);
}

auto CbOp::cycles() -> unsigned { return indirect_ ? 4 : 2; }

void CbOp::execute(RegistersInterface& registers, IMemoryView& memory)
{
  auto op = indirect_ ? memory.getLocation(hlp::indirect(*registers.get(WordRegister::HL))) : registers.get(operand_);
  switch (function_) {
  case CbFunction::RotateRight:
    apply(registers.getFlags(), ops::rrc(*op));
    break;
  case CbFunction::RotateRightCarry:
    apply(registers.getFlags(), ops::rr(*op, registers.getFlags().carry()));
    break;
  case CbFunction::RotateLeft:
    apply(registers.getFlags(), ops::rlc(*op));
    break;
  case CbFunction::RotateLeftCarry:
    apply(registers.getFlags(), ops::rl(*op, registers.getFlags().carry()));
    break;
  case CbFunction::ShiftRightArithmetic:
    apply(registers.getFlags(), ops::sra(*op));
    break;
  case CbFunction::ShiftLeftArithmetic:
    apply(registers.getFlags(), ops::sla(*op));
    break;
  case CbFunction::ShiftRightLogic:
    apply(registers.getFlags(), ops::srl(*op));
    break;
  case CbFunction::Swap:
    apply(registers.getFlags(), ops::swap(*op));
    break;
  case CbFunction::Bit:
    apply(registers.getFlags(), ops::bit(*op, affectedBit_));
    break;
  case CbFunction::Set:
    apply(registers.getFlags(), ops::set(*op, affectedBit_));
    break;
  case CbFunction::Reset:
    apply(registers.getFlags(), ops::reset(*op, affectedBit_));
    break;
  default:
    throw std::logic_error("Unimplemented.");
  }
}

void CbOp::setAffectedBit(uint8_t value)
{
  if (value > MaxBit) {
    throw std::invalid_argument("Only bits 0..7 addressable");
  }
  affectedBit_ = value;
}
