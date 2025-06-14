#include "jump.h"

#include <stdexcept>

#include "../registers/flagsview.h"
#include "../registers/registersinterface.h"
#include "mem/ilocation8.h"
#include "mem/imemoryview.h"
#include "mem/rest/variablelocation.h"
#include "ops/arithmetic.h"
#include "util/helpers.h"

Jump::Jump(JumpType type, TargetType target, Condition condition)
    : type_(type)
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

void Jump::nextOpcode(const ILocation8& opcode)
{
  if (type_ != JumpType::Regular && type_ != JumpType::Call && type_ != JumpType::Reset) {
    throw std::logic_error("Needs no immediate data.");
  }
  if (!immediateL_) {
    immediateL_ = std::make_unique<VariableLocation8>(variableLocation(opcode.get()));
  } else if (!immediateH_) {
    immediateH_ = std::make_unique<VariableLocation8>(variableLocation(opcode.get()));
  } else {
    throw std::logic_error("Enough opcodes already");
  }
}

auto Jump::isComplete() -> bool
{
  switch (type_) {
  case JumpType::Regular:
    return taken_.has_value() && immediateL_ && (target_ != TargetType::Absolute || immediateH_);
  case JumpType::Call:
  case JumpType::Reset:
    return taken_.has_value() && immediateL_ && immediateH_;
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

void Jump::execute(RegistersInterface& registers, IMemoryWordView& memory)
{
  auto& pc = registers.get(WordRegister::PC);
  if (!taken_) {
    throw std::logic_error("Registers not shown");
  }
  if (*taken_) {
    if (target_ == TargetType::Absolute) {
      auto& sp = registers.get(WordRegister::SP);
      switch (type_) {
      case JumpType::Call:
      case JumpType::Reset:
        // push PC
        ops::decrement(sp);
        ops::decrement(sp);
        {
          auto& memLoc = memory.getLocation16(hlp::indirect(sp));
          memLoc = registers.get(WordRegister::PC).get();
        }
        [[fallthrough]];
      case JumpType::Regular:
        if (!immediateL_) {
          throw std::invalid_argument("Adress location bytes not configured");
        } else if (!immediateH_) {
          throw std::invalid_argument("Only single byte provided, two are needed.");
        }
        pc = FusedLocation16::construct(immediateL_.get(), immediateH_.get()).get();
        break;
      case JumpType::Indirect:
        pc = registers.get(WordRegister::HL).get();
        break;
      case JumpType::RetI:
        registers.getFlags().enableInterrupt();
        [[fallthrough]];
      case JumpType::Return:
        pc = memory.getLocation16(hlp::indirect(sp)).get();
        ops::increment(sp);
        ops::increment(sp);
      }
    } else /*if (target_ == TargetType::Relative)*/ {
      if (!immediateL_) {
        throw std::invalid_argument("Adress location byte not configured");
      }
      ops::addSigned(pc, immediateL_->get());
    }
  }
}
