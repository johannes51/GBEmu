#include "gbchannel3.h"

#include "constants.h"
#include "util/helpers.h"

GbChannel3::GbChannel3(IRegisterAdapterSP nr30, IRegisterAdapterSP nr31, IRegisterAdapterSP nr32,
    IRegisterAdapterSP nr33, IRegisterAdapterSP nr34, IRegisterAdapterSP nr52, IMemoryViewSP waveRam)
    : Channel(std::move(nr52))
    , nr32_(std::move(nr32))
    , period_(std::move(nr33), nr34)
    , len_(std::move(nr31), std::move(nr34))
    , waveRam_(std::move(waveRam))
    , waveRamPtr_({ WaveRamStart, false })
{
  if (!nr32_ || !waveRam_) {
    throw std::invalid_argument("Audio registers not set.");
  }
  nr30.reset();
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
  auto ramSample = waveRam_->getLocation8(waveRamPtr_.address)->get();
  if (waveRamPtr_.upper) {
    ramSample = hlp::getBits(ramSample, HALF_BYTE_SHIFT, HALF_BYTE_SHIFT);
  } else {
    ramSample = hlp::getBits(ramSample, 0U, HALF_BYTE_SHIFT);
  }
  switch (hlp::getBits(nr32_->get(), VolumePatternBitPos, 2U)) {
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
