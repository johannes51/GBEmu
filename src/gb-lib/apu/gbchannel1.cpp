#include "gbchannel1.h"

GbChannel1::GbChannel1(IoBank& io, IRegisterAdapter& nr52)
    : GbPulseChannel(io, Nr10Adress, nr52)
    , sweep_(nr10_, nrX3_, nrX4_)
{
  io.registerRegister(Nr10Adress, &nr10_);
}

void GbChannel1::tickApuDiv(const FrameSequence sequence)
{
  GbPulseChannel::tickApuDiv(sequence);
  if (sequence == FrameSequence::Phase2 || sequence == FrameSequence::Phase6) {
    sweep_.clock();
  }
}
