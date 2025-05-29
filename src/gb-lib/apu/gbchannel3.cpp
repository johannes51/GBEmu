#include "gbchannel3.h"

#include "constants.h"
#include "util/helpers.h"

GbChannel3::GbChannel3(IoBank& io, IRegisterAdapter& nr52, IMemoryView& waveRam)
    : Channel(nr52)
    , period_(nr33_, nr34_)
    , len_(nr31_, nr34_)
    , waveRam_(waveRam)
    , waveRamPtr_({ WaveRamStart, false })
{
  io.registerRegister(Nr30Adress + 0U, &nr30_);
  io.registerRegister(Nr30Adress + 1U, &nr31_);
  io.registerRegister(Nr30Adress + 2U, &nr32_);
  io.registerRegister(Nr30Adress + 3U, &nr33_);
  io.registerRegister(Nr30Adress + 4U, &nr34_);
  // TODO: CH3 dac control
}

void GbChannel3::clock()
{
  if (period_.clockIsDone()) {
    advanceWaveRam();
  }
}

void GbChannel3::tickApuDiv(const FrameSequence sequence)
{
  switch (sequence) {
  case FrameSequence::Phase0:
  case FrameSequence::Phase2:
  case FrameSequence::Phase4:
  case FrameSequence::Phase6:
    len_.clock();
    if (len_.isRunOut()) {
      disable();
    }
    break;
  default:
    break;
  }
}

void GbChannel3::advanceWaveRam()
{
  auto ramSample = waveRam_.getLocation8(waveRamPtr_.address).get();
  if (waveRamPtr_.upper) {
    ramSample = hlp::getBits(ramSample, NIBBLE_SHIFT, NIBBLE_SHIFT);
  } else {
    ramSample = hlp::getBits(ramSample, 0U, NIBBLE_SHIFT);
  }
  switch (hlp::getBits(nr32_.getByte(), VolumePatternBit, 2U)) {
  case VolumePattern0Pct:
    ramSample = 0U;
    break;
  case VolumePattern100Pct:
    // ramSample >>= 0U;
    break;
  case VolumePattern50Pct:
    ramSample >>= 1U;
    break;
  case VolumePattern25Pct:
    ramSample >>= 2U;
    break;
  default: // NOTE: unreachable LCOV_EXCL_LINE
    break; // LCOV_EXCL_LINE
  }
  dac_.set(ramSample);
  if (waveRamPtr_.upper) {
    waveRamPtr_.upper = false;
  } else if (++waveRamPtr_.address > WaveRamTop) {
    waveRamPtr_.address = WaveRamStart;
    waveRamPtr_.upper = true;
  }
}
