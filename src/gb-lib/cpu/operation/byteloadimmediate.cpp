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

void ByteLoadImmediate::nextOpcode(const Location8& opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already done");
  }
  immediate_ = std::make_unique<Location8>(variableLocation(opcode.get()));
}

auto ByteLoadImmediate::isComplete() -> bool { return static_cast<bool>(immediate_); }

auto ByteLoadImmediate::cycles() -> unsigned { return indirect_ ? 3 : 2; }

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
void ByteLoadImmediate::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  if (!isComplete()) {
    throw std::invalid_argument("No immediate value configured");
  }
  if (indirect_) {
    memory.getLocation8(hlp::indirect(registers.get(WordRegister::HL))) = immediate_->get();
  } else {
    registers.get(destRegister_) = immediate_->get();
  }
}
