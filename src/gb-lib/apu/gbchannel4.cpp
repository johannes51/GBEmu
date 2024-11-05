#include "gbchannel4.h"

#include "util/helpers.h"

GbChannel4::GbChannel4(IRegisterAdapterSP nr41, IRegisterAdapterSP nr42, IRegisterAdapterSP nr43,
    IRegisterAdapterSP nr44, IRegisterAdapterSP nr52)
    : Channel(std::move(nr52))
    , nr43_(std::move(nr43))
    , len_(std::move(nr41), std::move(nr44))
    , env_(std::move(nr42))
{
  if (!nr43_) {
    throw std::invalid_argument("Audio registers not set.");
  }
  loadPeriod();
}

void GbChannel4::clock()
{
  if (--period_ == 0U) {
    shift();
    loadPeriod();
  }
}

void GbChannel4::tickApuDiv(const FrameSequence sequence)
{
  switch (sequence) {
  case FrameSequence::Phase0:
  case FrameSequence::Phase2:
  case FrameSequence::Phase4:
  case FrameSequence::Phase6:
    len_.clock();
    if (len_.isRunOut()) {
      disable();
    }
    break;
  default:
    break;
  }
}

void GbChannel4::shift()
{
  const auto newBit = (hlp::checkBit(lsfr_, LsfrFeedBit1) ^ hlp::checkBit(lsfr_, LsfrFeedBit2)) == 1U;
  hlp::writeBit(lsfr_, LsfrHighBit, newBit);
  if (nr43_->testBit(LsfrWidthBit)) {
    hlp::writeBit(lsfr_, LsfrLowBit, newBit);
  }
  lsfr_ >>= 1U;
  dac_.set((lsfr_ & 1U) * env_.vol());
}

void GbChannel4::loadPeriod()
{
  period_ = DivisorTable[hlp::getBits(nr43_->get(), DivisorBits.first, DivisorBits.second)]
      << hlp::getBits(nr43_->get(), ShiftBits.first, ShiftBits.second);
}
