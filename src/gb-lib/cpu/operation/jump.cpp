#include "jump.h"

#include <stdexcept>

#include "cpu/flagsview.h"
#include "cpu/registersinterface.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "ops/arithmetic.h"
#include "ops/memory.h"
#include "util/helpers.h"

Jump::Jump(JumpType type, TargetType target, Condition condition)
    : param_(nullptr)
    , type_(type)
    , target_(target)
    , condition_(condition)
    , taken_(std::nullopt)
{
  if (condition_ == Condition::None) {
    taken_ = true;
  }
}

Jump::~Jump() = default;

void Jump::showFlags(const FlagsView& flags)
{
  switch (condition_) {
  case Condition::Z:
    taken_ = flags.zero();
    break;
  case Condition::NZ:
    taken_ = !flags.zero();
    break;
  case Condition::C:
    taken_ = flags.carry();
    break;
  case Condition::NC:
    taken_ = !flags.carry();
    break;
  case Condition::None:
    break; // already true by constructor
  }
}

void Jump::nextOpcode(LocationUP opcode)
{
  if (!param_) {
    param_ = std::move(opcode);
  } else if (!param_->isWord()) {
    param_->fuse(*opcode);
  } else {
    throw std::logic_error("Enough opcodes already");
  }
}

auto Jump::isComplete() -> bool
{
  switch (type_) {
  case JumpType::Regular:
    return taken_.has_value() && param_ && (target_ != TargetType::Absolute || param_->isWord());
  case JumpType::Call:
    return taken_.has_value() && param_ && param_->isWord();
  default:
    return taken_.has_value();
  }
}

auto Jump::cycles() -> unsigned
{
  if (!taken_) {
    throw std::logic_error("Flags not shown");
  }
  unsigned result = 0;
  if (target_ == TargetType::Absolute) {
    switch (type_) {
    case JumpType::Indirect:
      result = 1;
      break;
    case JumpType::Regular:
      result = *taken_ ? TakenJump : SkippedJump;
      break;
    case JumpType::Call:
      result = *taken_ ? TakenCall : SkippedCall;
      break;
    case JumpType::Return:
    case JumpType::RetI:
    case JumpType::Reset:
      if (condition_ == Condition::None) {
        result = NormalReturn;
      } else {
        result = *taken_ ? TakenReturn : SkippedReturn;
      }
      break;
    }
  } else /*if (target_ == TargetType::Relative)*/ {
    result = *taken_ ? 3 : 2;
  }
  return result;
}

void Jump::execute(RegistersInterface& registers, IMemoryView& memory)
{
  auto pc = registers.get(WordRegister::PC);
  if (!taken_) {
    throw std::logic_error("Registers not shown");
  }
  if (*taken_) {
    if (target_ == TargetType::Absolute) {
      auto sp = registers.get(WordRegister::SP);
      switch (type_) {
      case JumpType::Call:
      case JumpType::Reset:
        ops::decrement<uint16_t>(*sp);
        ops::decrement<uint16_t>(*sp);
        {
          auto memLoc = memory.getLocation(hlp::indirect(*sp), true);
          ops::load<uint16_t>(*memLoc, *registers.get(WordRegister::PC));
        }
        [[fallthrough]];
      case JumpType::Regular:
        if (!param_) {
          throw std::invalid_argument("Adress location bytes not configured");
        }
        ops::load<uint16_t>(*pc, *param_);
        break;
      case JumpType::Indirect:
        ops::load<uint16_t>(*pc, *registers.get(WordRegister::HL));
        break;
      case JumpType::RetI:
        registers.getFlags().enableInterrupt();
        [[fallthrough]];
      case JumpType::Return:
        ops::load<uint16_t>(*pc, *memory.getLocation(hlp::indirect(*sp)));
        ops::increment<uint16_t>(*sp);
        ops::increment<uint16_t>(*sp);
      }
    } else /*if (target_ == TargetType::Relative)*/ {
      if (!param_) {
        throw std::invalid_argument("Adress location byte not configured");
      }
      ops::addSigned(*pc, *param_);
    }
  }
}
