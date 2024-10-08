#include "byteloadstandard.h"

#include "ops/memory.h"

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
  ops::load<uint8_t>(*registers.get(destRegister_), *registers.get(srcRegister_));
}
