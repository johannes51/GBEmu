#ifndef GBCHANNEL2_H
#define GBCHANNEL2_H

#include "channel_util/gbpulsechannel.h"

class GbChannel2 : public GbPulseChannel {
public:
  GbChannel2(IoBank& io, IRegisterAdapter& nr52);

private:
  static constexpr address_type Nr20Adress = 0xFF15U;

  bool channelOn_ = false;
};

#endif // GBCHANNEL2_H
