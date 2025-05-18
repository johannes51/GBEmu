#include "sweep.h"

#include "constants.h"
#include "util/helpers.h"

Sweep::Sweep(const IRegisterAdapter& nr10, IRegisterAdapter& nr13, IRegisterAdapter& nr14)
    : nr10_(nr10)
    , nr13_(nr13)
    , nr14_(nr14)
{
  loadCounter();
}

void Sweep::clock()
{
  if (counter_ != 0U) {
    --counter_;
    if (counter_ == 0U) {
      modifyPeriod();
      loadCounter();
    }
  }
}

void Sweep::loadCounter() { counter_ = hlp::getBits(nr10_.getByte(), CounterBit, CounterBitCount); }

void Sweep::modifyPeriod()
{
  const auto step = hlp::getBits(nr10_.getByte(), 0U, StepBitCount);
  const auto oldPeriod = static_cast<uint16_t>(nr13_.getByte())
      | static_cast<uint16_t>(static_cast<uint16_t>(nr14_.getByte() & CounterPeriodMask) << BYTE_SHIFT);

  const auto divisor = (1U << step);
  const auto change = (oldPeriod / divisor);
  uint16_t newPeriod = oldPeriod;
  if (nr10_.testBit(DirectionBit)) {
    newPeriod -= change;
  } else {
    newPeriod += change;
  }
  nr13_.setByte(newPeriod & LOWER_BYTE_MASK);
  nr14_.setByte(nr14_.getByte() | static_cast<uint8_t>(newPeriod >> BYTE_SHIFT));
}
