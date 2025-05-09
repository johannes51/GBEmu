#include "fusedlocation16.h"

#include "constants.h"

FusedLocation16::FusedLocation16(Location8UP lower, Location8UP upper)
    : Location16()
    , lower_(std::move(lower))
    , upper_(std::move(upper))
{
}

auto FusedLocation16::get() const -> uint16_t
{
  return (static_cast<uint16_t>(static_cast<uint16_t>(upper_->get()) << BYTE_SHIFT) | lower_->get());
}

auto FusedLocation16::operator=(const uint16_t& rhs) -> FusedLocation16&
{
  *lower_ = rhs & BYTE_MASK;
  *upper_ = rhs >> BYTE_SHIFT;
  return *this;
}

auto FusedLocation16::hasLower() const -> bool { return static_cast<bool>(lower_); }

auto FusedLocation16::hasUpper() const -> bool { return static_cast<bool>(upper_); }

auto FusedLocation16::lower() const -> uint8_t { return lower_->get(); }

auto FusedLocation16::upper() const -> uint8_t { return upper_->get(); }

void FusedLocation16::setLower(Location8UP value) { lower_ = std::move(value); }

void FusedLocation16::setUpper(Location8UP value) { upper_ = std::move(value); }
