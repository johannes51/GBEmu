#include "aluoperation.h"

#include <stdexcept>

#include "location/location.h"
#include "mem/imemoryview.h"
#include "util/helpers.h"
#include "util/ops.h"

AluOperation::AluOperation(AluFunction function, Source source)
    : function_(function)
    , source_(source)
    , register_(std::nullopt)
    , immediate_(std::nullopt)

{
}

AluOperation::~AluOperation() = default;

void AluOperation::nextOpcode(Location<uint8_t> opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already complete");
  }
  immediate_ = Location<uint8_t>(std::move(opcode));
}

auto AluOperation::isComplete() -> bool { return source_ != Source::Immediate || immediate_; }

void AluOperation::setRegister(ByteRegisters registerName) { register_ = registerName; }

auto AluOperation::cycles() -> unsigned int
{
  unsigned int result = 1;
  if (source_ == Source::Indirect) {
    ++result;
    if (function_ == AluFunction::Dec) {
      ++result;
    }
  } else if (source_ == Source::Immediate) {
    ++result;
  }
  return result;
}

void AluOperation::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  switch (function_) {
  case AluFunction::Add:
    ops::add(registers.get(ByteRegisters::A), getSource(registers, memory));
    break;
  case AluFunction::Dec:
    if (source_ == Source::Indirect) {
      ops::decrement(getSource(registers, memory));
    } else {
      ops::decrement(registers.get(*register_));
    }
    break;
  case AluFunction::Xor:
    ops::xorF(registers.get(ByteRegisters::A), getSource(registers, memory));
    break;
  }
}

auto AluOperation::getSource(RegistersInterface& reg, IMemoryView& mem) -> Location<uint8_t>
{
  switch (source_) {
  case Source::Immediate:
    return std::move(*immediate_);
    break;
  case Source::Indirect:
    return mem.getByte(hlp::indirect(reg.get(WordRegisters::HL)));
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
