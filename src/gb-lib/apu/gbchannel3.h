#ifndef GBCHANNEL3_H
#define GBCHANNEL3_H

#include "channel.h"

#include "channel_util/lengthch3.h"
#include "channel_util/period.h"
#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"

class GbChannel3 : public Channel {
public:
  GbChannel3(const IRegisterAdapter& nr30, const IRegisterAdapter& nr31, const IRegisterAdapter& nr32,
      const IRegisterAdapter& nr33, const IRegisterAdapter& nr34, IRegisterAdapter& nr52, IMemoryView& waveRam);

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

  const IRegisterAdapter& nr32_;

  Period period_;
  LengthCh3 len_;

  IMemoryView& waveRam_;
  WaveRamLocation waveRamPtr_;

  void advanceWaveRam();
};

#endif // GBCHANNEL3_H
