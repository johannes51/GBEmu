#include "lengthch3.h"

LengthCh3::LengthCh3(const IRegisterAdapter& nr31, const IRegisterAdapter& nr34)
    : nr31_(nr31)
    , nr34_(nr34)
{
  setCounter();
}

void LengthCh3::clock()
{
  checkEnable();
  if (counter_ != LEN_INACTIVE && counter_ != LEN_STOPPED) {
    if (++counter_ == LEN_MAX_VAL) {
      counter_ = LEN_STOPPED;
    }
  }
}

auto LengthCh3::isRunOut() const -> bool { return counter_ == LEN_STOPPED; }

void LengthCh3::checkEnable()
{
  if (!nr34_.testBit(LenEnableBit)) {
    counter_ = LEN_INACTIVE;
  } else if (counter_ == LEN_INACTIVE) {
    setCounter();
  }
}

void LengthCh3::setCounter() { counter_ = nr31_.getByte(); }
