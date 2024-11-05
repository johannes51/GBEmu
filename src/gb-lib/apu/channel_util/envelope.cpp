#include "envelope.h"

#include "util/helpers.h"

Envelope::Envelope(IRegisterAdapterSP nrX2)
    : nrX2_(std::move(nrX2))
{
  if (!nrX2_) {
    throw std::invalid_argument("Audio registers not set.");
  }
  volume_ = readVolume();
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

void Envelope::readCounter() { counter_ = hlp::getBits(nrX2_->get(), CounterBits.first, CounterBits.second); }

void Envelope::moveVol()
{
  if (nrX2_->testBit(3U)) {
    if (volume_ < MaxVolume) {
      ++volume_;
    }
  } else {
    if (volume_ > 0U) {
      --volume_;
    }
  }
}

auto Envelope::readVolume() const -> uint8_t { return nrX2_->get() >> 4U; }
