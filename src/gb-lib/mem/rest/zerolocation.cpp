#include "zerolocation.h"

uint8_t ZeroByteLocation::zero_ = { 0U };

auto ZeroByteLocation::get() const -> const uint8_t& { return zero_; }

void ZeroByteLocation::set(const uint8_t& value) { (void)value; }

auto ZeroByteLocation::copy() -> ByteLocationAdapterUP { return std::make_unique<ZeroByteLocation>(); }

uint16_t ZeroWordLocation::zero_ = { 0U };

auto ZeroWordLocation::get() const -> const uint16_t& { return zero_; }

void ZeroWordLocation::set(const uint16_t& value) { (void)value; }

auto ZeroWordLocation::copy() -> WordLocationAdapterUP { return std::make_unique<ZeroWordLocation>(); }
