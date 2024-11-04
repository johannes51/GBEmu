#include "sweep.h"

#include "constants.h"

Sweep::Sweep(IRegisterAdapterSP nr10, IRegisterAdapterSP nr13, IRegisterAdapterSP nr14)
    : nr10_(std::move(nr10))
    , nr13_(std::move(nr13))
    , nr14_(std::move(nr14))
{
  if (!nr10_ || !nr13_ || !nr14_) {
    throw std::invalid_argument("Audio registers not set.");
  }
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

void Sweep::loadCounter() { counter_ = (nr10_->get() >> 4U) & 0b111U; }

void Sweep::modifyPeriod()
{
  const auto step = nr10_->get() & 0b111U;
  auto bla1 = nr13_->get();
  auto bla2 = static_cast<uint16_t>(nr14_->get() & 0b111U) << BYTE_SHIFT;
  const auto oldPeriod
      = static_cast<uint16_t>(nr13_->get()) | (static_cast<uint16_t>(nr14_->get() & 0b111U) << BYTE_SHIFT);
  const auto up = (nr10_->get() & 0b1000U) == 0U;

  const auto divisor = (1U << step);
  const auto change = (oldPeriod / divisor);
  uint16_t newPeriod = oldPeriod;
  if (up) {
    newPeriod += change;
  } else {
    newPeriod -= change;
  }
  nr13_->set(newPeriod & 0xFFU);
  nr14_->set(nr14_->get() | static_cast<uint8_t>(newPeriod >> BYTE_SHIFT));
}
