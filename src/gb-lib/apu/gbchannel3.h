#ifndef GBCHANNEL3_H
#define GBCHANNEL3_H

#include "channel.h"

#include "channel_util/lengthch3.h"
#include "channel_util/period.h"
#include "io/iobank.h"
#include "io/ioregister.h"
#include "io/iregisteradapter.h"
#include "mem/imemoryview.h"

class GbChannel3 : public Channel {
public:
  GbChannel3(IoBank& io, IRegisterAdapter& nr52, IMemoryView& waveRam);

  void clock() override;
  void tickApuDiv(const FrameSequence sequence) override;

private:
  struct WaveRamLocation {
    address_type address;
    bool upper;
  };

  static constexpr address_type Nr30Adress = 0xFF1AU;

  static constexpr uint16_t WaveRamStart = 0xFF30U;
  static constexpr uint16_t WaveRamTop = 0xFF3FU;

  static constexpr uint8_t VolumePattern0Pct = 0b00U;
  static constexpr uint8_t VolumePattern100Pct = 0b01U;
  static constexpr uint8_t VolumePattern50Pct = 0b10U;
  static constexpr uint8_t VolumePattern25Pct = 0b11U;
  static constexpr uint8_t VolumePatternBit = 5U;

  IoRegister nr30_;
  IoRegister nr31_;
  IoRegister nr32_;
  IoRegister nr33_;
  IoRegister nr34_;

  Period period_;
  LengthCh3 len_;

  IMemoryView& waveRam_;
  WaveRamLocation waveRamPtr_;

  void advanceWaveRam();
};

#endif // GBCHANNEL3_H
