#ifndef GBCHANNEL1_H
#define GBCHANNEL1_H

#include "channel_util/gbpulsechannel.h"

#include "channel_util/sweep.h"
#include "io/iobank.h"
#include "io/iregisteradapter.h"

class GbChannel1 : public GbPulseChannel {
public:
  explicit GbChannel1(IoBank& io, IRegisterAdapter& nr52);

  void tickApuDiv(const FrameSequence sequence) override;

private:
  static constexpr address_type Nr10Adress = 0xFF10U;

  FixedMaskIoRegister<0b10000000U> nr10_;
  Sweep sweep_;
};

#endif // GBCHANNEL1_H
