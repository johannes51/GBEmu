#include "jump.h"

#include <cstring>
#include <stdexcept>

#include "cpu/flagsview.h"
#include "cpu/registersinterface.h"
#include "location/location.h"
#include "location/zerobyte.h"
#include "util/ops.h"

Jump::Jump(JumpType type, Condition condition)
    : lower_(std::nullopt)
    , upper_(std::nullopt)
    , type_(type)
    , condition_(condition)
{
}

Jump::~Jump() = default;

void Jump::nextOpcode(Location<uint8_t> opcode)
{
  if (!lower_) {
    lower_ = std::move(opcode);
  } else if (!upper_) {
    upper_ = std::move(opcode);
  } else {
    throw std::logic_error("Enough opcodes already");
  }
}

auto Jump::isComplete() -> bool
{
  auto result = true;
  switch (type_) {
  case JumpType::Absolute:
    result = lower_ && upper_;
    break;
  case JumpType::Relative:
    result = static_cast<bool>(lower_);
    break;
  }
  return result;
}

auto Jump::cycles(const RegistersInterface& registers) -> unsigned int
{
  unsigned int result = 0;
  if (type_ == JumpType::Absolute) {
    result = taken(registers.getFlags()) ? 4 : 3;
  } else if (type_ == JumpType::Relative) {
    result = taken(registers.getFlags()) ? 3 : 2;
  }
  return result;
}

void Jump::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  auto target = registers.get(WordRegisters::PC);
  if (taken(registers.getFlags())) {
    switch (type_) {
    case JumpType::Absolute:
      ops::load(target, Location<uint8_t>::fuse(std::move(*lower_), std::move(*upper_)));
      break;
    case JumpType::Relative:
      auto operandUnsigned = lower_->get();
      int8_t operand = 0;
      std::memcpy(
          &operand, &operandUnsigned, sizeof(operand)); // WARNING: this only works as 2's complement (so always)
      ops::add(target, operand);
      break;
    }
  }
}

auto Jump::taken(const FlagsView& flags) const -> bool
{
  auto result = true;
  switch (condition_) {
  case Condition::Z:
    result = flags.zero();
    break;
  case Condition::NZ:
    result = !flags.zero();
    break;
  case Condition::C:
    result = flags.carry();
    break;
  case Condition::NC:
    result = !flags.carry();
    break;
  default:
    break;
  }
  return result;
}
