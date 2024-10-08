#include "zerolocation.h"

std::array<uint8_t, 2> ZeroLocation::zero_ = { 0 };

const uint8_t& ZeroLocation::getByte() const { return zero_.front(); }

const uint16_t& ZeroLocation::getWord() const { return *reinterpret_cast<uint16_t*>(&zero_.front()); }

Location& ZeroLocation::operator=(const uint8_t& rhs)
{
  (void)rhs;
  return *this;
}

Location& ZeroLocation::operator=(const uint16_t& rhs)
{
  (void)rhs;
  return *this;
}
