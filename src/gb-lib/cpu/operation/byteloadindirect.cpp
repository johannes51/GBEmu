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
void ByteLoadIndirect::execute(RegistersInterface& registers, IMemoryWordView& memory)
{
  auto& memLocation = memory.getLocation8(hlp::indirect(registers.get(indirectRegister_)));
  auto& registerLocation = registers.get(directRegister_);
  if (direction_ == Direction::Indirect) {
    memLocation = registerLocation.get();
  } else /*if (direction_ == Direction::Register)*/ {
    registerLocation = memLocation.get();
  }
  auto& indirReg = registers.get(indirectRegister_);
  switch (postAction_) {
  case Post::Increment:
    ops::increment(indirReg);
    break;
  case Post::Decrement:
    ops::decrement(indirReg);
    break;
  default:
    break;
  }
}
