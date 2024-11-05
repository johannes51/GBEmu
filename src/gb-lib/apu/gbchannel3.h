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
  void tickApuDiv(const FrameSequence sequence) override;

private:
  struct WaveRamLocation {
    address_type address;
    bool upper;
  };

  static constexpr uint16_t WaveRamStart = 0xFF30U;
  static constexpr uint16_t WaveRamTop = 0xFF3FU;

  static constexpr uint8_t VolumePattern0Pct = 0b00U;
  static constexpr uint8_t VolumePattern100Pct = 0b01U;
  static constexpr uint8_t VolumePattern50Pct = 0b10U;
  static constexpr uint8_t VolumePattern25Pct = 0b11U;
  static constexpr uint8_t VolumePatternBitPos = 5U;

  IRegisterAdapterSP nr32_;

  Period period_;
  LengthCh3 len_;

  IMemoryViewSP waveRam_;
  WaveRamLocation waveRamPtr_;

  void advanceWaveRam();
};

#endif // GBCHANNEL3_H
