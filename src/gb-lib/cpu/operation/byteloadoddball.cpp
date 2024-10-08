#include "byteloadoddball.h"

// #include <stdexcept>

// #include "cpu/registersinterface.h"
// #include "location/location.h"
#include "mem/imemoryview.h"
// #include "ops/arithmetic.h"
#include "ops/memory.h"
#include "util/helpers.h"

ByteLoadOddball::ByteLoadOddball(Direction direction, Indirection indirection)
    : direction_(direction)
    , indirection_(indirection)
    , immediate_(nullptr)
{
}

ByteLoadOddball::~ByteLoadOddball() = default;

void ByteLoadOddball::nextOpcode(LocationUP opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already done");
  }
  if (!immediate_) {
    immediate_ = std::move(opcode);
  } else if (!immediate_->isWord()) {
    immediate_->fuse(*opcode);
  }
}

auto ByteLoadOddball::isComplete() -> bool
{
  switch (indirection_) {
  case Indirection::RegisterC:
    return true;
    break;
  case Indirection::ImmediateStandard:
    return static_cast<bool>(immediate_) && immediate_->isWord();
    break;
  case Indirection::ImmediateZeroPage:
    return static_cast<bool>(immediate_);
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
  address_type indirAdress;
  switch (indirection_) {
  case Indirection::RegisterC:
    indirAdress = hlp::indirect(*registers.get(ByteRegister::C));
    break;
  case Indirection::ImmediateStandard:
    indirAdress = hlp::indirect(*immediate_);
    break;
  case Indirection::ImmediateZeroPage:
    indirAdress = hlp::indirectZeroPage(*immediate_);
    break;
  }
  const auto indirLoc = memory.getLocation(indirAdress);
  const auto registerA = registers.get(ByteRegister::A);

  if (direction_ == Direction::Register) {
    ops::load<uint8_t>(*registerA, *indirLoc);
  } else /*if (direction_ == Direction::Register)*/ {
    ops::load<uint8_t>(*indirLoc, *registerA);
  }
}
