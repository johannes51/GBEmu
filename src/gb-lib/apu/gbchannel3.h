#ifndef GBCHANNEL3_H
#define GBCHANNEL3_H

#include "channel.h"

#include "channel_util/lengthch3.h"
#include "channel_util/period.h"
#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"

class GbChannel3 : public Channel {
public:
  GbChannel3(IRegisterAdapterSP nr30, IRegisterAdapterSP nr31, IRegisterAdapterSP nr32, IRegisterAdapterSP nr33,
      IRegisterAdapterSP nr34, IRegisterAdapterSP nr52, IMemoryViewSP waveRam);

  void clock() override;
  void tickApuDiv(const uint8_t frameSequencerStep) override;

private:
  struct WaveRamLocation {
    address_type address;
    bool upper;
  };

  IRegisterAdapterSP nr32_;

  Period period_;
  LengthCh3 len_;

  IMemoryViewSP waveRam_;
  WaveRamLocation waveRamPtr_;

  void advanceWaveRam();
};

#endif // GBCHANNEL3_H
