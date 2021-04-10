#include "bytealuoperation.h"

#include <stdexcept>

#include "cpu/flagsview.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "util/helpers.h"
#include "util/ops.h"

ByteAluOperation::ByteAluOperation(ByteAluFunction function, Source source)
    : function_(function)
    , source_(source)
    , register_(std::nullopt)
    , immediate_(std::nullopt)
{
}

void ByteAluOperation::nextOpcode(Location<uint8_t> opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already complete");
  }
  immediate_ = Location<uint8_t>(std::move(opcode));
}

auto ByteAluOperation::isComplete() -> bool { return source_ != Source::Immediate || immediate_; }

void ByteAluOperation::setRegister(ByteRegister registerName) { register_ = registerName; }

auto ByteAluOperation::cycles(const RegistersInterface& registers) -> unsigned int
{
  (void)registers;
  unsigned int result = 1;
  if (source_ == Source::Indirect) {
    ++result;
    if (function_ == ByteAluFunction::Inc || function_ == ByteAluFunction::Dec) {
      ++result;
    }
  } else if (source_ == Source::Immediate) {
    ++result;
  }
  return result;
}

void ByteAluOperation::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  ops::OpResult result { 0, 0, 0, 0 };
  switch (function_) {
  case ByteAluFunction::Add: {
    auto loc = registers.get(ByteRegister::A);
    result = ops::add(loc, getSource(registers, memory));
    break;
  }
  case ByteAluFunction::Inc: {
    Location<uint8_t> loc;
    if (source_ == Source::Indirect) {
      loc = getSource(registers, memory);
    } else {
      loc = registers.get(*register_);
    }
    result = ops::increment(loc);
    break;
  }
  case ByteAluFunction::Dec: {
    Location<uint8_t> loc;
    if (source_ == Source::Indirect) {
      loc = getSource(registers, memory);
    } else {
      loc = registers.get(*register_);
    }
    result = ops::decrement(loc);
    break;
  }
  case ByteAluFunction::Or: {
    auto loc = registers.get(ByteRegister::A);
    result = ops::orF(loc, getSource(registers, memory));
    break;
  }
  case ByteAluFunction::Xor: {
    auto loc = registers.get(ByteRegister::A);
    result = ops::xorF(loc, getSource(registers, memory));
    break;
  }
  case ByteAluFunction::Cp: {
    auto loc = registers.get(ByteRegister::A);
    result = ops::cpF(loc, getSource(registers, memory));
    break;
  }
  }
  apply(registers.getFlags(), result);
}

auto ByteAluOperation::getSource(RegistersInterface& reg, IMemoryView& mem) -> Location<uint8_t>
{
  switch (source_) {
  case Source::Immediate:
    return std::move(*immediate_);
    break;
  case Source::Indirect:
    return mem.getByte(hlp::indirect(reg.get(WordRegister::HL)));
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

void ByteAluOperation::apply(FlagsView& flags, const ops::OpResult& result)
{
  if (result.z == 0) {
    flags.clearZero();
  } else if (result.z == 1) {
    flags.setZero();
  }
  //  if (result.c == 0) {
  //    flags.clearCarry();
  //  } else if (result.c == 1) {
  //    flags.setCarry();
  //  }
}
