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

void CpuFlags::setHalfCarry() { hlp::setBit(buffer_, HALF_CARRY_BIT); }

void CpuFlags::clearHalfCarry() { hlp::clearBit(buffer_, HALF_CARRY_BIT); }

auto CpuFlags::halfCarry() const -> bool { return hlp::checkBit(buffer_, HALF_CARRY_BIT); }

void CpuFlags::setSubtract() { hlp::setBit(buffer_, SUBTRACT_BIT); }

void CpuFlags::clearSubtract() { hlp::clearBit(buffer_, SUBTRACT_BIT); }

auto CpuFlags::subtract() const -> bool { return hlp::checkBit(buffer_, SUBTRACT_BIT); }

void CpuFlags::setCarry() { hlp::setBit(buffer_, CARRY_BIT); }

void CpuFlags::clearCarry() { hlp::clearBit(buffer_, CARRY_BIT); }

auto CpuFlags::carry() const -> bool { return hlp::checkBit(buffer_, CARRY_BIT); }

void CpuFlags::enableInterrupt() { interrupt_ = true; }

void CpuFlags::disableInterrupt() { interrupt_ = false; }

auto CpuFlags::interruptEnabled() const -> bool { return interrupt_; }
