#include "bytealuoperation.h"

#include <stdexcept>

#include "../registers/flagsview.h"
#include "mem/ilocation8.h"
#include "mem/imemoryview.h"
#include "mem/rest/variablelocation.h"
#include "ops/arithmetic.h"
#include "ops/logic.h"
#include "util/helpers.h"

ByteAluOperation::ByteAluOperation(ByteAluFunction function, Source source)
    : function_(function)
    , source_(source)
    , register_(std::nullopt)
    , immediate_()
{
  if (source == Source::None) {
    throw std::invalid_argument("source can't be None");
  }
}

void ByteAluOperation::nextOpcode(const ILocation8& opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already complete");
  }
  immediate_ = std::make_unique<VariableLocation8>(variableLocation(opcode.get()));
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

void ByteAluOperation::execute(RegistersInterface& registers, IMemoryWordView& memory)
{
  (void)memory;
  ops::OpResult result {
    .z = ops::FlagResult::Reset, .n = ops::FlagResult::Reset, .h = ops::FlagResult::Reset, .c = ops::FlagResult::Reset
  };

  auto& regA = registers.get(ByteRegister::A);
  switch (function_) {
  case ByteAluFunction::Add:
    result = ops::add(regA, getSource(registers, memory));
    break;
  case ByteAluFunction::AddCarry:
    result = ops::add_carry(regA, getSource(registers, memory), registers.getFlags().carry());
    break;
  case ByteAluFunction::Sub:
    result = ops::sub(regA, getSource(registers, memory));
    break;
  case ByteAluFunction::SubCarry:
    result = ops::sub_carry(regA, getSource(registers, memory), registers.getFlags().carry());
    break;
  case ByteAluFunction::Inc: {
    auto& loc = getSource(registers, memory);
    result = ops::increment(loc);
    break;
  }
  case ByteAluFunction::Dec: {
    auto& loc = getSource(registers, memory);
    result = ops::decrement(loc);
    break;
  }
  case ByteAluFunction::And: {
    result = ops::andF(regA, getSource(registers, memory));
    break;
  }
  case ByteAluFunction::Or: {
    result = ops::orF(regA, getSource(registers, memory));
    break;
  }
  case ByteAluFunction::Xor: {
    result = ops::xorF(regA, getSource(registers, memory));
    break;
  }
  case ByteAluFunction::Cp: {
    result = ops::cpF(regA, getSource(registers, memory));
    break;
  }
  }
  apply(registers.getFlags(), result);
}

auto ByteAluOperation::getSource(RegistersInterface& reg, IMemoryView& mem) -> ILocation8&
{
  switch (source_) {
  case Source::Immediate:
    if (!immediate_) {
      throw std::invalid_argument("No immediate value configured");
    }
    return *immediate_;
    break;
  case Source::Indirect:
    return mem.getLocation8(hlp::indirect(reg.get(WordRegister::HL)));
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
