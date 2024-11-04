#ifndef GBCHANNEL1_H
#define GBCHANNEL1_H

#include "channel_util/gbpulsechannel.h"

#include "channel_util/sweep.h"
#include "mem/registers/iregisteradapter.h"

class GbChannel1 : public GbPulseChannel {
public:
  GbChannel1(IRegisterAdapterSP nr10, IRegisterAdapterSP nr11, IRegisterAdapterSP nr12, IRegisterAdapterSP nr13,
      IRegisterAdapterSP nr14, IRegisterAdapterSP nr52);

  void tickApuDiv(const uint8_t frameSequencerStep) override;

private:
  IRegisterAdapterSP nr10_;

  Sweep sweep_;
};

#endif // GBCHANNEL1_H
