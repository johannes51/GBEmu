#include "cpuflags.h"

CpuFlags::CpuFlags(uint8_t& buffer)
    : buffer_(buffer)
    , interrupt_(true)
{
}

void CpuFlags::setZero() { setBit(ZERO_BIT); }

void CpuFlags::clearZero() { clearBit(ZERO_BIT); }

auto CpuFlags::zero() const -> bool { return checkBit(ZERO_BIT); }

void CpuFlags::setCarry() { setBit(CARRY_BIT); }

void CpuFlags::clearCarry() { clearBit(CARRY_BIT); }

auto CpuFlags::carry() const -> bool { return checkBit(CARRY_BIT); }

void CpuFlags::enableInterrupt() { interrupt_ = true; }

void CpuFlags::disableInterrupt() { interrupt_ = false; }

auto CpuFlags::interruptEnabled() const -> bool { return interrupt_; }

void CpuFlags::setBit(uint8_t pos) { buffer_ |= (1ULL << pos); }

void CpuFlags::clearBit(uint8_t pos) { buffer_ &= ~(1ULL << pos); }

auto CpuFlags::checkBit(uint8_t pos) const -> bool { return (buffer_ & (1U << pos)) != 0; }
