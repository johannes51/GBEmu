#include "bytealuoperation.h"

#include <stdexcept>

#include "cpu/flagsview.h"
#include "location/location8.h"
#include "mem/imemoryview.h"
#include "ops/arithmetic.h"
#include "ops/logic.h"
#include "util/helpers.h"

ByteAluOperation::ByteAluOperation(ByteAluFunction function, Source source)
    : function_(function)
    , source_(source)
    , register_(std::nullopt)
    , immediate_(std::nullopt)
{
  if (source == Source::None) {
    throw std::invalid_argument("source can't be None");
  }
}

void ByteAluOperation::nextOpcode(Location8UP opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already complete");
  }
  immediate_ = std::move(opcode);
}

auto ByteAluOperation::isComplete() -> bool
{
  return (source_ == Source::Register && register_) || (source_ == Source::Immediate && immediate_)
      || (source_ != Source::Register && source_ != Source::Immediate);
}

void ByteAluOperation::setRegister(ByteRegister registerName) { register_ = registerName; }

auto ByteAluOperation::cycles() -> unsigned
{
  if (source_ == Source::Immediate) {
    return 2;
  } else if (source_ == Source::Indirect) {
    if (function_ == ByteAluFunction::Inc || function_ == ByteAluFunction::Dec) {
      return 3;
    } else {
      return 2;
    }
  } else {
    return 1;
  }
}

void ByteAluOperation::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  ops::OpResult result {
    .z = ops::FlagResult::Reset, .n = ops::FlagResult::Reset, .h = ops::FlagResult::Reset, .c = ops::FlagResult::Reset
  };
  switch (function_) {
  case ByteAluFunction::Add:
    result = ops::add(*registers.get(ByteRegister::A), *getSource(registers, memory));
    break;
  case ByteAluFunction::AddCarry:
    result
        = ops::add_carry(*registers.get(ByteRegister::A), *getSource(registers, memory), registers.getFlags().carry());
    break;
  case ByteAluFunction::Sub:
    result = ops::sub(*registers.get(ByteRegister::A), *getSource(registers, memory));
    break;
  case ByteAluFunction::SubCarry:
    result
        = ops::sub_carry(*registers.get(ByteRegister::A), *getSource(registers, memory), registers.getFlags().carry());
    break;
  case ByteAluFunction::Inc: {
    auto loc = getSource(registers, memory);
    result = ops::increment(*loc);
    break;
  }
  case ByteAluFunction::Dec: {
    auto loc = getSource(registers, memory);
    result = ops::decrement(*loc);
    break;
  }
  case ByteAluFunction::And: {
    auto loc = registers.get(ByteRegister::A);
    result = ops::andF(*loc, *getSource(registers, memory));
    break;
  }
  case ByteAluFunction::Or: {
    auto loc = registers.get(ByteRegister::A);
    result = ops::orF(*loc, *getSource(registers, memory));
    break;
  }
  case ByteAluFunction::Xor: {
    auto loc = registers.get(ByteRegister::A);
    result = ops::xorF(*loc, *getSource(registers, memory));
    break;
  }
  case ByteAluFunction::Cp: {
    auto loc = registers.get(ByteRegister::A);
    result = ops::cpF(*loc, *getSource(registers, memory));
    break;
  }
  }
  apply(registers.getFlags(), result);
}

auto ByteAluOperation::getSource(RegistersInterface& reg, IMemoryView& mem) -> Location8UP
{
  switch (source_) {
  case Source::Immediate:
    if (!immediate_) {
      throw std::invalid_argument("No immediate value configured");
    }
    return std::move(*immediate_);
    break;
  case Source::Indirect:
    return mem.getLocation8(hlp::indirect(*reg.get(WordRegister::HL)));
    break;
  case Source::Register:
    if (!register_) {
      throw std::invalid_argument("No register set");
    }
    return reg.get(*register_);
    break;
  case Source::None:
  default:
    throw std::invalid_argument("No proper source configured");
    break;
  }
}
