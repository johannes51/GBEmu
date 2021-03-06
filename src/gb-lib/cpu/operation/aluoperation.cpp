#include "aluoperation.h"

#include <stdexcept>

#include "location/location.h"
#include "util/ops.h"

AluOperation::AluOperation(AluFunction function, Source source)
  : function_(function)
  , source_(source)
  , register_(std::nullopt)
  , immediate_()
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

bool AluOperation::isComplete() { return source_ != Source::Immediate || register_; }

void AluOperation::setRegister(ByteRegisters registerName) { register_ = registerName; }

unsigned int AluOperation::cycles() {
  unsigned int result;
  if (source_ == Source::Indirect) {
    if (function_ == AluFunction::Dec) { result = 3; }
    else { result = 2; }
  } else {
    result = 1;
  }
  return result;
}

void AluOperation::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  switch (function_) {
  case AluFunction::Xor:
    ops::xorF(registers.get(ByteRegisters::A), getSource(registers));
    break;
  case AluFunction::Dec:
    ops::decrement(registers.get(*register_));
    break;
  }
}

Location<uint8_t> AluOperation::getSource(RegistersInterface& registers)
{
  switch (source_) {
  case Source::Immediate:
    return std::move(*immediate_);
    break;
  case Source::Indirect:
    throw std::logic_error("Indirect source uninmplemented");
    break;
  case Source::Register:
    if (!register_) {
      throw std::invalid_argument("No register set");
    }
    return registers.get(*register_);
    break;
  case Source::None:
    throw std::invalid_argument("Source-less operation");
    break;
  }
  throw std::logic_error("shouldn't get here");
}
