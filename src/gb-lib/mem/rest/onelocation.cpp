#include "onelocation.h"

uint8_t OneLocation::one_ = { 0xFFU }; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

auto OneLocation::get() const -> const uint8_t& { return one_; }

auto OneLocation::operator=(const uint8_t& rhs) -> OneLocation&
{
  (void)rhs;
  return *this;
}

auto OneLocation::instance() -> ILocation8&
{
  static OneLocation l;
  return l;
}
