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
  if (type_ == JumpType::Relative) {
    upper_ = Location<uint8_t>::generate(std::make_unique<ZeroByte>());
  }
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
  auto taken = true;
  switch (condition_) {
  case Condition::Z:
    taken = registers.getFlags().zero();
    break;
  case Condition::NZ:
    taken = !registers.getFlags().zero();
    break;
  case Condition::C:
    taken = registers.getFlags().carry();
    break;
  case Condition::NC:
    taken = !registers.getFlags().carry();
    break;
  default:
    break;
  }
  if (type_ == JumpType::Absolute) {
    return taken ? 4 : 3;
  } else if (type_ == JumpType::Relative) {
    return taken ? 3 : 2;
  }
  throw std::logic_error("Unimplemented JP type");
}

void Jump::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  switch (type_) {
  case JumpType::Absolute:
    ops::load(registers.get(WordRegisters::PC), Location<uint8_t>::fuse(std::move(*lower_), std::move(*upper_)));
    break;
  case JumpType::Relative:
    auto operandUnsigned = lower_->get();
    int8_t operand = 0;
    std::memcpy(&operand, &operandUnsigned, sizeof(operand)); // WARNING: this only works as 2's complement (so always)
    ops::add(registers.get(WordRegisters::PC), operand);
    break;
  }
}
