#include "jump.h"

#include <stdexcept>

#include "cpu/flagsview.h"
#include "cpu/registersinterface.h"
#include "location/location8.h"
#include "location/variablelocation.h"
#include "mem/imemoryview.h"
#include "ops/arithmetic.h"
#include "util/helpers.h"

Jump::Jump(JumpType type, TargetType target, Condition condition)
    : param_(nullptr, nullptr)
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

void Jump::nextOpcode(Location8UP opcode)
{
  if (type_ != JumpType::Regular && type_ != JumpType::Call && type_ != JumpType::Reset) {
    throw std::logic_error("Needs no immediate data.");
  }
  if (!param_.hasLower()) {
    param_.setLower(std::move(opcode));
  } else if (!param_.hasUpper()) {
    param_.setUpper(std::move(opcode));
  } else {
    throw std::logic_error("Enough opcodes already");
  }
}

auto Jump::isComplete() -> bool
{
  switch (type_) {
  case JumpType::Regular:
    return taken_.has_value() && param_.hasLower() && (target_ != TargetType::Absolute || param_.hasUpper());
  case JumpType::Call:
  case JumpType::Reset:
    return taken_.has_value() && param_.hasLower() && param_.hasUpper();
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
        ops::decrement(*sp);
        ops::decrement(*sp);
        {
          auto memLoc = memory.getLocation16(hlp::indirect(*sp));
          *memLoc = registers.get(WordRegister::PC)->get();
        }
        [[fallthrough]];
      case JumpType::Regular:
        if (!param_.hasLower()) {
          throw std::invalid_argument("Adress location bytes not configured");
        } else if (!param_.hasUpper()) {
          throw std::invalid_argument("Only single byte provided, two are needed.");
        }
        *pc = param_.get();
        break;
      case JumpType::Indirect:
        *pc = registers.get(WordRegister::HL)->get();
        break;
      case JumpType::RetI:
        registers.getFlags().enableInterrupt();
        [[fallthrough]];
      case JumpType::Return:
        *pc = memory.getLocation16(hlp::indirect(*sp))->get();
        ops::increment(*sp);
        ops::increment(*sp);
      }
    } else /*if (target_ == TargetType::Relative)*/ {
      if (!param_.hasLower()) {
        throw std::invalid_argument("Adress location byte not configured");
      }
      auto signedLocation = variableLocation(param_.lower());
      ops::addSigned(*pc, *signedLocation);
    }
  }
}
