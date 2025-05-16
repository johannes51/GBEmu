#include "envelope.h"

#include "util/helpers.h"

Envelope::Envelope(const IRegisterAdapter& nrX2)
    : nrX2_(nrX2)
    , volume_(readVolume())
{
  readCounter();
}

void Envelope::clock()
{
  if (counter_ != 0U) {
    if (--counter_ == 0U) {
      moveVol();
      readCounter();
    }
  }
}

auto Envelope::vol() const -> uint8_t { return volume_; }

void Envelope::readCounter() { counter_ = hlp::getBits(nrX2_.getByte(), CounterBits.first, CounterBits.second); }

void Envelope::moveVol()
{
  if (nrX2_.testBit(3U)) {
    if (volume_ < MaxVolume) {
      ++volume_;
    }
  } else {
    if (volume_ > 0U) {
      --volume_;
    }
  }
}

auto Envelope::readVolume() const -> uint8_t { return nrX2_.getByte() >> 4U; }
