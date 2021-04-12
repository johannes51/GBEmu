#include "cpuflags.h"

#include "util/helpers.h"

CpuFlags::CpuFlags(uint8_t& buffer)
    : buffer_(buffer)
    , interrupt_(true)
{
}

void CpuFlags::setZero() { hlp::setBit(buffer_, ZERO_BIT); }

void CpuFlags::clearZero() { hlp::clearBit(buffer_, ZERO_BIT); }

auto CpuFlags::zero() const -> bool { return hlp::checkBit(buffer_, ZERO_BIT); }

void CpuFlags::setCarry() { hlp::setBit(buffer_, CARRY_BIT); }

void CpuFlags::clearCarry() { hlp::clearBit(buffer_, CARRY_BIT); }

auto CpuFlags::carry() const -> bool { return hlp::checkBit(buffer_, CARRY_BIT); }

void CpuFlags::enableInterrupt() { interrupt_ = true; }

void CpuFlags::disableInterrupt() { interrupt_ = false; }

auto CpuFlags::interruptEnabled() const -> bool { return interrupt_; }
