#include "envelope.h"

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
  if (counter_ != 0U && --counter_ == 0U) {
    moveVol();
    readCounter();
  }
}

auto Envelope::vol() -> uint8_t { return volume_; }

void Envelope::readCounter() { counter_ = nrX2_->get() & 0b111U; }

void Envelope::moveVol()
{
  if (nrX2_->testBit(3U)) {
    if (volume_ < 0b1111) {
      ++volume_;
    }
  } else {
    if (volume_ > 0U) {
      --volume_;
    }
  }
}

auto Envelope::readVolume() const -> uint8_t { return nrX2_->get() >> 4U; }
