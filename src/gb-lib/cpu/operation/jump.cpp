#include "jump.h"

#include <stdexcept>

#include "cpu/registersinterface.h"
#include "location/location.h"
#include "location/zerobyte.h"
#include "util/ops.h"

Jump::Jump(JumpType type)
    : lower_(std::nullopt)
    , upper_(std::nullopt)
    , type_(type)
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
  bool result = true;
  switch (type_) {
  case JumpType::Direct:
    result = lower_ && upper_;
    break;
  case JumpType::Relative:
    result = static_cast<bool>(lower_);
    break;
  }
  return result;
}

auto Jump::cycles() -> unsigned int { return 4; }

void Jump::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  switch (type_) {
  case JumpType::Direct:
    ops::load(registers.get(WordRegisters::PC), Location<uint8_t>::fuse(std::move(*lower_), std::move(*upper_)));
    break;
  case JumpType::Relative:
    ops::add(registers.get(WordRegisters::PC), Location<uint8_t>::fuse(std::move(*lower_), std::move(*upper_)));
    break;
  }
}
