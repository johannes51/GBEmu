#include "pushpop.h"

// #include <stdexcept>

// #include "cpu/registersinterface.h"
// #include "location/location8.h"
#include "mem/imemoryview.h"
#include "ops/arithmetic.h"
// #include "ops/memory.h"
#include "util/helpers.h"

PushPop::PushPop(Direction direction, WordRegister targetRegister)
    : direction_(direction)
    , targetRegister_(targetRegister)
{
}

auto PushPop::cycles() -> unsigned { return direction_ == Direction::Pop ? 3 : 4; }

void PushPop::execute(RegistersInterface& registers, IMemoryView& memory)
{
  auto sp = registers.get(WordRegister::SP);
  if (direction_ == Direction::Push) {
    ops::decrement(*sp);
    ops::decrement(*sp);
  }
  auto stackLoc = memory.getLocation16(hlp::indirect(*sp));
  if (direction_ == Direction::Pop) {
    ops::increment(*sp);
    ops::increment(*sp);
  }
  auto target = registers.get(targetRegister_);

  switch (direction_) {
  case Direction::Push:
    *stackLoc = target->get();
    break;
  case Direction::Pop:
    *target = stackLoc->get();
    break;
  case Direction::Invalid:
    [[fallthrough]];
  default:
    throw std::invalid_argument("No direction specified!");
    break;
  }
}
