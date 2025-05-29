#include "fusedlocation16.h"

#include "constants.h"

FusedLocation16::FusedLocation16(ILocation8* lower, ILocation8* upper)
    : lower_(lower)
    , upper_(upper)
    , buffer_()
{
  reloadBuffer();
}

auto FusedLocation16::get() const -> const uint16_t& { return buffer_; }

auto FusedLocation16::operator=(const uint16_t& rhs) -> FusedLocation16&
{
  *lower_ = rhs & BYTE_MASK;
  *upper_ = rhs >> BYTE_SHIFT;
  buffer_ = rhs;
  return *this;
}

auto FusedLocation16::hasLower() const -> bool { return lower_ != nullptr; }

auto FusedLocation16::hasUpper() const -> bool { return upper_ != nullptr; }

auto FusedLocation16::lower() const -> uint8_t { return lower_->get(); }

auto FusedLocation16::upper() const -> uint8_t { return upper_->get(); }

void FusedLocation16::setLower(ILocation8* value)
{
  lower_ = value;
  reloadBuffer();
}

void FusedLocation16::setUpper(ILocation8* value)
{
  upper_ = value;
  reloadBuffer();
}

auto FusedLocation16::construct(ILocation8* lower, ILocation8* upper) -> FusedLocation16
{
  return FusedLocation16 { lower, upper };
}

void FusedLocation16::reloadBuffer()
{
  if (hasLower() && hasUpper()) {
    buffer_ = lower_->get() | static_cast<uint16_t>(upper_->get() << BYTE_SHIFT);
  }
}
