#include "period.h"

#include "constants.h"
#include "util/helpers.h"

Period::Period(const IRegisterAdapter& nrX3, const IRegisterAdapter& nrX4)
    : nrX3_(nrX3)
    , nrX4_(nrX4)
    , period_(MaxPeriod)
{
  load();
}

auto Period::clockIsDone() -> bool
{
  if (--period_ == 0U) {
    load();
    return true;
  } else {
    return false;
  }
}

void Period::load()
{
  const auto frequency
      = static_cast<uint16_t>(hlp::getBits(static_cast<uint16_t>(nrX4_.getByte()), 0U, PeriodMsbCount) << BYTE_SHIFT)
      | nrX3_.getByte();
  period_ = MaxPeriod - frequency;
}
