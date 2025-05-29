#include "byteloadoddball.h"

// #include <stdexcept>

#include "mem/common/fusedlocation16.h"
#include "mem/imemoryview.h"
#include "mem/rest/variablelocation.h"
#include "util/helpers.h"

ByteLoadOddball::ByteLoadOddball(Direction direction, Indirection indirection)
    : direction_(direction)
    , indirection_(indirection)
{
}

ByteLoadOddball::~ByteLoadOddball() = default;

void ByteLoadOddball::nextOpcode(const ILocation8& opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already done");
  }
  if (!immediateL_ && !immediateH_) {
    immediateL_ = std::make_unique<VariableLocation8>(variableLocation(opcode.get()));
  } else if (!immediateH_) {
    immediateH_ = std::make_unique<VariableLocation8>(variableLocation(opcode.get()));
  }
}

auto ByteLoadOddball::isComplete() -> bool
{
  switch (indirection_) {
  case Indirection::RegisterC:
    return true;
    break;
  case Indirection::ImmediateStandard:
    return static_cast<bool>(immediateL_) && static_cast<bool>(immediateH_);
    break;
  case Indirection::ImmediateZeroPage:
    return static_cast<bool>(immediateL_);
    break;
  default:
    throw std::logic_error("Unreachable");
    break;
  }
}

auto ByteLoadOddball::cycles() -> unsigned
{
  switch (indirection_) {
  case Indirection::RegisterC:
    return 2;
    break;
  case Indirection::ImmediateStandard:
    return 4;
    break;
  case Indirection::ImmediateZeroPage:
    return 3;
    break;
  default:
    throw std::logic_error("Unreachable");
    break;
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
void ByteLoadOddball::execute(RegistersInterface& registers, IMemoryWordView& memory)
{
  address_type indirAdress = 0U;
  switch (indirection_) {
  case Indirection::RegisterC:
    indirAdress = hlp::indirectZeroPage(registers.get(ByteRegister::C));
    break;
  case Indirection::ImmediateStandard: {
    const FusedLocation16 l { immediateL_.get(), immediateH_.get() };
    indirAdress = hlp::indirect(l);
    break;
  }
  case Indirection::ImmediateZeroPage:
    indirAdress = hlp::indirectZeroPage(*immediateL_);
    break;
  }
  auto& indirLoc = memory.getLocation8(indirAdress);
  auto& registerA = registers.get(ByteRegister::A);

  if (direction_ == Direction::Register) {
    registerA = indirLoc.get();
  } else /*if (direction_ == Direction::Register)*/ {
    indirLoc = registerA.get();
  }
}
