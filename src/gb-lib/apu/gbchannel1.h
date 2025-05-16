#ifndef GBCHANNEL1_H
#define GBCHANNEL1_H

#include "channel_util/gbpulsechannel.h"

#include "channel_util/sweep.h"
#include "mem/registers/iregisteradapter.h"

class GbChannel1 : public GbPulseChannel {
public:
  GbChannel1(const IRegisterAdapter& nr10, const IRegisterAdapter& nr11, const IRegisterAdapter& nr12,
      IRegisterAdapter& nr13, IRegisterAdapter& nr14, IRegisterAdapter& nr52);

  void tickApuDiv(const FrameSequence sequence) override;

private:
  const IRegisterAdapter& nr10_;

  Sweep sweep_;
};

#endif // GBCHANNEL1_H
