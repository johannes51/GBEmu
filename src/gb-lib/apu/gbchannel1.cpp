#include "gbchannel1.h"

GbChannel1::GbChannel1(const IRegisterAdapter& nr10, const IRegisterAdapter& nr11, const IRegisterAdapter& nr12,
    IRegisterAdapter& nr13, IRegisterAdapter& nr14, IRegisterAdapter& nr52)
    : GbPulseChannel(nr11, nr12, nr13, nr14, nr52)
    , nr10_(nr10)
    , sweep_(nr10, nr13, nr14)
{
}

void GbChannel1::tickApuDiv(const FrameSequence sequence)
{
  GbPulseChannel::tickApuDiv(sequence);
  if (sequence == FrameSequence::Phase2 || sequence == FrameSequence::Phase6) {
    sweep_.clock();
  }
}
