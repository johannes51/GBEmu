#include "zerolocation.h"

#include <array>

std::array<uint8_t, 2> ZeroLocation::zero_ = { 0 };

auto ZeroLocation::getByte() const -> const uint8_t& { return zero_.front(); }

auto ZeroLocation::getWord() const -> const uint16_t& { return *reinterpret_cast<uint16_t*>(&zero_.front()); }

auto ZeroLocation::operator=(const uint8_t& rhs) -> ZeroLocation&
{
  (void)rhs;
  return *this;
}

auto ZeroLocation::operator=(const uint16_t& rhs) -> ZeroLocation&
{
  (void)rhs;
  return *this;
}
