#include "byteloadstandard.h"

ByteLoadStandard::ByteLoadStandard(ByteRegister destRegister, ByteRegister srcRegister)
    : destRegister_(destRegister)
    , srcRegister_(srcRegister)
{
}

ByteLoadStandard::~ByteLoadStandard() = default;

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
void ByteLoadStandard::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  registers.get(destRegister_) = registers.get(srcRegister_).get();
}
