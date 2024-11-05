#ifndef GBCHANNEL2_H
#define GBCHANNEL2_H

#include "channel_util/gbpulsechannel.h"

#include "mem/registers/iregisteradapter.h"

class GbChannel2 : public GbPulseChannel {
public:
  GbChannel2(IRegisterAdapterSP nr21, IRegisterAdapterSP nr22, IRegisterAdapterSP nr23, IRegisterAdapterSP nr24,
      IRegisterAdapterSP nr52);

private:
  bool channelOn_ = false;
};

#endif // GBCHANNEL2_H
