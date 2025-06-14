#include "cbop.h"

#include <stdexcept>

#include "cpu/id/cbopdecoder.h"
#include "mem/ilocation8.h"
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

auto CbOp::cycles() -> unsigned
{
  if (indirect_) {
    return function_ != CbFunction::Bit ? 4U : 3U;
  } else {
    return 2U;
  }
}

void CbOp::execute(RegistersInterface& registers, IMemoryWordView& memory)
{
  if (!isComplete()) {
    throw std::logic_error("No bit set on bit op.");
  }
  auto& op = indirect_ ? memory.getLocation8(hlp::indirect(registers.get(WordRegister::HL))) : registers.get(operand_);
  switch (function_) {
  case CbFunction::RotateRight:
    apply(registers.getFlags(), ops::rr(op, registers.getFlags().carry()));
    break;
  case CbFunction::RotateRightCiruclar:
    apply(registers.getFlags(), ops::rr(op));
    break;
  case CbFunction::RotateLeft:
    apply(registers.getFlags(), ops::rl(op, registers.getFlags().carry()));
    break;
  case CbFunction::RotateLeftCircular:
    apply(registers.getFlags(), ops::rl(op));
    break;
  case CbFunction::ShiftRightArithmetic:
    apply(registers.getFlags(), ops::sra(op));
    break;
  case CbFunction::ShiftLeftArithmetic:
    apply(registers.getFlags(), ops::sla(op));
    break;
  case CbFunction::ShiftRightLogic:
    apply(registers.getFlags(), ops::srl(op));
    break;
  case CbFunction::Swap:
    apply(registers.getFlags(), ops::swap(op));
    break;
  case CbFunction::Bit:
    apply(registers.getFlags(), ops::bit(op, affectedBit_));
    break;
  case CbFunction::Set:
    ops::set(op, affectedBit_);
    break;
  case CbFunction::Reset:
    ops::reset(op, affectedBit_);
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
