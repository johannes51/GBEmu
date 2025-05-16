#include "length.h"

Length::Length(const IRegisterAdapter& nrX1, const IRegisterAdapter& nrX4)
    : nrX1_(nrX1)
    , nrX4_(nrX4)
{
  ;
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
  if (!nrX4_.testBit(LenEnableBitPos)) {
    counter_ = LEN_INACTIVE;
  } else if (counter_ == LEN_INACTIVE) {
    setCounter();
  }
}

void Length::setCounter() { counter_ = nrX1_.getByte() & CounterMask; }
