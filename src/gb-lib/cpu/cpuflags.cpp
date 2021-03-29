#include "cpuflags.h"

CpuFlags::CpuFlags(uint8_t& buffer)
    : buffer_(buffer)
    , carry_(false)
    , interrupt_(true)
{
}

void CpuFlags::setCarry() { carry_ = true; }

void CpuFlags::clearCarry() { carry_ = false; }

auto CpuFlags::carry() -> bool
{
  (void)buffer_;
  return carry_;
}

void CpuFlags::enableInterrupt() { interrupt_ = true; }

void CpuFlags::disableInterrupt() { interrupt_ = false; }

auto CpuFlags::interruptEnabled() -> bool { return interrupt_; }
