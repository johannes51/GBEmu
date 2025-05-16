#include "fusedlocation16.h"

#include "constants.h"

FusedLocation16::FusedLocation16(std::unique_ptr<Location8> lower, std::unique_ptr<Location8> upper)
    : lower_(std::move(lower))
    , upper_(std::move(upper))
    , buffer_()
{
  reloadBuffer();
}

auto FusedLocation16::get() const -> const uint16_t& { return buffer_; }

void FusedLocation16::set(const uint16_t& value)
{
  *lower_ = value & BYTE_MASK;
  *upper_ = value >> BYTE_SHIFT;
  buffer_ = value;
}

auto FusedLocation16::hasLower() const -> bool { return static_cast<bool>(lower_); }

auto FusedLocation16::hasUpper() const -> bool { return static_cast<bool>(upper_); }

auto FusedLocation16::lower() const -> uint8_t { return lower_->get(); }

auto FusedLocation16::upper() const -> uint8_t { return upper_->get(); }

void FusedLocation16::setLower(std::unique_ptr<Location8>&& value)
{
  lower_ = std::move(value);
  reloadBuffer();
}

void FusedLocation16::setUpper(std::unique_ptr<Location8>&& value)
{
  upper_ = std::move(value);
  reloadBuffer();
}

void FusedLocation16::reloadBuffer()
{
  if (hasLower() && hasUpper()) {
    buffer_ = lower_->get() | static_cast<uint16_t>(upper_->get() << BYTE_SHIFT);
  }
}
