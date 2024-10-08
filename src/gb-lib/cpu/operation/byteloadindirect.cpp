#include "byteloadindirect.h"

#include "mem/imemoryview.h"
#include "ops/arithmetic.h"
#include "util/helpers.h"

ByteLoadIndirect::ByteLoadIndirect(
    Direction direction, ByteRegister directRegister, WordRegister indirectRegister, Post postAction)
    : direction_(direction)
    , directRegister_(directRegister)
    , indirectRegister_(indirectRegister)
    , postAction_(postAction)
{
}

ByteLoadIndirect::~ByteLoadIndirect() = default;

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
void ByteLoadIndirect::execute(RegistersInterface& registers, IMemoryView& memory)
{
  auto memLocation = memory.getLocation(hlp::indirect(*registers.get(indirectRegister_)));
  auto registerLocation = registers.get(directRegister_);
  if (direction_ == Direction::Indirect) {
    *memLocation = registerLocation->getByte();
  } else /*if (direction_ == Direction::Register)*/ {
    *registerLocation = memLocation->getByte();
  }
  switch (postAction_) {
  case Post::Increment:
    ops::increment<uint16_t>(*registers.get(indirectRegister_));
    break;
  case Post::Decrement:
    ops::decrement<uint16_t>(*registers.get(indirectRegister_));
    break;
  default:
    break;
  }
}
