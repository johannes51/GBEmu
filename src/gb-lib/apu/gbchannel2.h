#ifndef GBCHANNEL2_H
#define GBCHANNEL2_H

#include "channel_util/gbpulsechannel.h"

#include "mem/registers/iregisteradapter.h"

class GbChannel2 : public GbPulseChannel {
public:
  GbChannel2(const IRegisterAdapter& nr21, const IRegisterAdapter& nr22, const IRegisterAdapter& nr23,
      const IRegisterAdapter& nr24, IRegisterAdapter& nr52);

private:
  bool channelOn_ = false;
};

#endif // GBCHANNEL2_H
