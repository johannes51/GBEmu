#include "byteloadoddball.h"

// #include <stdexcept>

#include "location/fusedlocation16.h"
#include "mem/imemoryview.h"
#include "util/helpers.h"

ByteLoadOddball::ByteLoadOddball(Direction direction, Indirection indirection)
    : direction_(direction)
    , indirection_(indirection)
    , immediate8_(nullptr)
{
}

ByteLoadOddball::~ByteLoadOddball() = default;

void ByteLoadOddball::nextOpcode(Location8UP opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already done");
  }
  if (!immediate8_ && !immediate16_) {
    immediate8_ = std::move(opcode);
  } else if (!immediate16_) {
    immediate16_ = std::make_unique<FusedLocation16>(std::move(immediate8_), std::move(opcode));
  }
}

auto ByteLoadOddball::isComplete() -> bool
{
  switch (indirection_) {
  case Indirection::RegisterC:
    return true;
    break;
  case Indirection::ImmediateStandard:
    return static_cast<bool>(immediate16_);
    break;
  case Indirection::ImmediateZeroPage:
    return static_cast<bool>(immediate8_);
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
void ByteLoadOddball::execute(RegistersInterface& registers, IMemoryView& memory)
{
  address_type indirAdress = 0U;
  switch (indirection_) {
  case Indirection::RegisterC:
    indirAdress = hlp::indirectZeroPage(*registers.get(ByteRegister::C));
    break;
  case Indirection::ImmediateStandard:
    indirAdress = hlp::indirect(*immediate16_);
    break;
  case Indirection::ImmediateZeroPage:
    indirAdress = hlp::indirectZeroPage(*immediate8_);
    break;
  }
  const auto indirLoc = memory.getLocation8(indirAdress);
  const auto registerA = registers.get(ByteRegister::A);

  if (direction_ == Direction::Register) {
    *registerA = indirLoc->get();
  } else /*if (direction_ == Direction::Register)*/ {
    *indirLoc = registerA->get();
  }
}
