#include "gbchannel1.h"

GbChannel1::GbChannel1(IRegisterAdapterSP nr10, IRegisterAdapterSP nr11, IRegisterAdapterSP nr12,
    IRegisterAdapterSP nr13, IRegisterAdapterSP nr14, IRegisterAdapterSP nr52)
    : GbPulseChannel(std::move(nr11), std::move(nr12), nr13, nr14, std::move(nr52))
    , nr10_(nr10)
    , sweep_(std::move(nr10), std::move(nr13), std::move(nr14))
{
  if (!nr10_) {
    throw std::invalid_argument("Audio registers not set.");
  }
}

void GbChannel1::tickApuDiv(const uint8_t frameSequencerStep)
{
  GbPulseChannel::tickApuDiv(frameSequencerStep);
  if (frameSequencerStep == 2U || frameSequencerStep == 6U) {
    sweep_.clock();
  }
}
