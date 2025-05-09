#include "byteloadimmediate.h"

#include "mem/imemoryview.h"
#include "util/helpers.h"

ByteLoadImmediate::~ByteLoadImmediate() = default;

ByteLoadImmediate::ByteLoadImmediate(ByteRegister destRegister)
    : destRegister_(destRegister)
    , indirect_(false)
    , immediate_(nullptr)
{
}

ByteLoadImmediate::ByteLoadImmediate(WordRegister destRegister)
    : ByteLoadImmediate(ByteRegister::None)
{
  if (destRegister == WordRegister::HL) {
    indirect_ = true;
  } else {
    throw std::invalid_argument("Can only load immediate indirect to HL");
  }
}

void ByteLoadImmediate::nextOpcode(Location8UP opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already done");
  }
  immediate_ = std::move(opcode);
}

auto ByteLoadImmediate::isComplete() -> bool { return immediate_ != nullptr; }

auto ByteLoadImmediate::cycles() -> unsigned { return indirect_ ? 3 : 2; }

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
void ByteLoadImmediate::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  if (!isComplete()) {
    throw std::invalid_argument("No immediate value configured");
  }
  Location8UP dest;
  if (indirect_) {
    dest = memory.getLocation8(hlp::indirect(*registers.get(WordRegister::HL)));
  } else {
    dest = registers.get(destRegister_);
  }
  *dest = immediate_->get();
}
