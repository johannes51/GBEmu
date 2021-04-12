#include "jump.h"

#include <stdexcept>

#include "cpu/flagsview.h"
#include "cpu/registersinterface.h"
#include "location/location.h"
#include "location/zerobyte.h"
#include "mem/imemoryview.h"
#include "ops/arithmetic.h"
#include "ops/memory.h"
#include "util/helpers.h"

Jump::Jump(JumpType type, TargetType target, Condition condition)
    : lower_(std::nullopt)
    , upper_(std::nullopt)
    , type_(type)
    , target_(target)
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
  if (type_ == JumpType::Return || type_ == JumpType::RetI) {
    result = true;
  } else {
    switch (target_) {
    case TargetType::Absolute:
      result = lower_ && upper_;
      break;
    case TargetType::Relative:
      result = static_cast<bool>(lower_);
      break;
    }
  }
  return result;
}

auto Jump::cycles(const RegistersInterface& registers) -> unsigned
{
  unsigned result = 0;
  if (target_ == TargetType::Absolute) {
    switch (type_) {
    case JumpType::Regular:
      result = taken(registers.getFlags()) ? TakenJump : SkippedJump;
      break;
    case JumpType::Call:
      result = taken(registers.getFlags()) ? TakenCall : SkippedCall;
      break;
    case JumpType::Return:
    case JumpType::RetI:
    case JumpType::Reset:
      result = (condition_ == Condition::None) ? NormalReturn
                                               : (taken(registers.getFlags()) ? TakenReturn : SkippedReturn);
      break;
    }
  } else /*if (target_ == TargetType::Relative)*/ {
    result = taken(registers.getFlags()) ? 3 : 2;
  }
  return result;
}

void Jump::execute(RegistersInterface& registers, IMemoryView& memory)
{
  auto pc = registers.get(WordRegister::PC);
  if (taken(registers.getFlags())) {
    if (target_ == TargetType::Absolute) {
      auto sp = registers.get(WordRegister::SP);
      switch (type_) {
      case JumpType::Call:
      case JumpType::Reset:
        ops::decrement(sp);
        ops::decrement(sp);
        {
          auto memLoc = memory.getWord(hlp::indirect(sp));
          ops::load(memLoc, registers.get(WordRegister::PC));
        }
        [[fallthrough]];
      case JumpType::Regular:
        ops::load(pc, Location<uint8_t>::fuse(std::move(*lower_), std::move(*upper_)));
        break;
      case JumpType::RetI:
        registers.getFlags().enableInterrupt();
        [[fallthrough]];
      case JumpType::Return:
        ops::load(pc, memory.getWord(hlp::indirect(sp)));
        ops::increment(sp);
        ops::increment(sp);
      }
    } else /*if (target_ == TargetType::Relative)*/ {
      ops::addSigned(pc, *lower_);
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
