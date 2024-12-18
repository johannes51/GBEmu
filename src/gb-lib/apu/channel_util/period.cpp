#include "period.h"

#include "constants.h"
#include "util/helpers.h"

Period::Period(IRegisterAdapterSP nrX3, IRegisterAdapterSP nrX4)
    : nrX3_(std::move(nrX3))
    , nrX4_(std::move(nrX4))
    , period_(MaxPeriod)
{
  if (!nrX3_ || !nrX4_) {
    throw std::invalid_argument("Audio registers not set.");
  }
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
      = static_cast<uint16_t>(hlp::getBits(static_cast<uint16_t>(nrX4_->get()), 0U, PeriodMsbCount) << BYTE_SHIFT)
      | nrX3_->get();
  period_ = MaxPeriod - frequency;
}
