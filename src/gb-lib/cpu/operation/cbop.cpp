#include "cbop.h"

#include <stdexcept>

#include "cpu/id/cbopdecoder.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "ops/shiftrotatebitwise.h"
#include "util/helpers.h"

CbOp::CbOp(CbFunction function, bool indirect, ByteRegister operand)
    : function_(function)
    , indirect_(indirect)
    , operand_(operand)
    , affectedBit_(0)
{
}

auto CbOp::cycles() -> unsigned
{
  if (!indirect_) {
    return 2;
  } else {
    if (function_ == CbFunction::Bit) {
      return 3;
    } else {
      return 4;
    }
  }
}

void CbOp::execute(RegistersInterface& registers, IMemoryView& memory)
{
  auto op = selectOperand(registers, memory);
  switch (function_) {
  case CbFunction::ShiftRightLogic:
    ops::srl(op);
    break;
  case CbFunction::RotateRight:
    ops::rr(op);
    break;
  case CbFunction::Swap:
    ops::swap(op);
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

auto CbOp::selectOperand(RegistersInterface& registers, IMemoryView& memory) -> Location<uint8_t>
{
  return indirect_ ? memory.getByte(hlp::indirect(registers.get(WordRegister::HL))) : registers.get(operand_);
}
