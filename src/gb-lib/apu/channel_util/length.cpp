#include "length.h"

Length::Length(IRegisterAdapterSP nrX1, IRegisterAdapterSP nrX4)
    : nrX1_(std::move(nrX1))
    , nrX4_(std::move(nrX4))
{
  if (!nrX1_ || !nrX4_) {
    throw std::invalid_argument("Audio registers not set.");
  }
  counter_ = LEN_INACTIVE;
}

void Length::clock()
{
  checkEnable();
  if (counter_ != LEN_INACTIVE && counter_ != LEN_STOPPED) {
    if (++counter_ == LEN_MAX_VAL) {
      counter_ = LEN_STOPPED;
    }
  }
}

auto Length::isRunOut() const -> bool { return counter_ == LEN_STOPPED; }

void Length::checkEnable()
{
  if (!nrX4_->testBit(6U)) {
    counter_ = LEN_INACTIVE;
  } else if (counter_ == LEN_INACTIVE) {
    setCounter();
  }
}

void Length::setCounter() { counter_ = nrX1_->get() & 0b111111U; }
