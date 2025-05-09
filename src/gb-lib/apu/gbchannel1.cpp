#include "gbchannel1.h"

GbChannel1::GbChannel1(IRegisterAdapterSP nr10, IRegisterAdapterSP nr11, IRegisterAdapterSP nr12,
    IRegisterAdapterSP nr13, IRegisterAdapterSP nr14, IRegisterAdapterSP nr52)
    : GbPulseChannel(std::move(nr11), std::move(nr12), nr13, nr14, std::move(nr52))
    , nr10_(nr10)
    , sweep_(std::move(nr10), std::move(nr13), std::move(nr14))
{
  if (!nr10_) {
    throw std::invalid_argument("Audio registers not set."); // NOTE: unreachable LCOV_EXCL_LINE
  }
}

void GbChannel1::tickApuDiv(const FrameSequence sequence)
{
  GbPulseChannel::tickApuDiv(sequence);
  if (sequence == FrameSequence::Phase2 || sequence == FrameSequence::Phase6) {
    sweep_.clock();
  }
}
