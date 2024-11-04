#include "gbchannel4.h"

#include "util/helpers.h"

GbChannel4::GbChannel4(IRegisterAdapterSP nr41, IRegisterAdapterSP nr42, IRegisterAdapterSP nr43,
    IRegisterAdapterSP nr44, IRegisterAdapterSP nr52)
    : Channel(std::move(nr52))
    , nr43_(nr43)
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

void GbChannel4::tickApuDiv(const uint8_t frameSequencerStep)
{
  if ((frameSequencerStep % 2U) == 0U) {
    len_.clock();
    if (len_.isRunOut()) {
      disable();
    }
  }
}

void GbChannel4::shift()
{
  const auto newBit = !(hlp::checkBit(lsfr_, 0U) ^ hlp::checkBit(lsfr_, 1U));
  hlp::writeBit(lsfr_, 15U, newBit);
  if (nr43_->testBit(3U)) {
    hlp::writeBit(lsfr_, 7U, newBit);
  }
  lsfr_ >>= 1U;
  dac_.set((lsfr_ & 1U) * env_.vol());
}

void GbChannel4::loadPeriod()
{
  period_ = DivisorTable[hlp::getBits(nr43_->get(), 0U, 3U)] << hlp::getBits(nr43_->get(), 4U, 4U);
}
