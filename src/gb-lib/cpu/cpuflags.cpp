#include "cpuflags.h"

CpuFlags::CpuFlags(uint8_t& buffer)
    : buffer_(buffer)
    , carry_(false)
{
}

void CpuFlags::setCarry() { carry_ = true; }

void CpuFlags::clearCarry() { carry_ = false; }

auto CpuFlags::carry() -> bool
{
  (void)buffer_;
  return carry_;
}
