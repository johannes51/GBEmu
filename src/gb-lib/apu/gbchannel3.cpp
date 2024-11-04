#include "gbchannel3.h"
#include "constants.h"

GbChannel3::GbChannel3(IRegisterAdapterSP nr30, IRegisterAdapterSP nr31, IRegisterAdapterSP nr32,
    IRegisterAdapterSP nr33, IRegisterAdapterSP nr34, IRegisterAdapterSP nr52, IMemoryViewSP waveRam)
    : Channel(std::move(nr52))
    , nr32_(std::move(nr32))
    , period_(std::move(nr33), nr34)
    , len_(std::move(nr31), std::move(nr34))
    , waveRam_(std::move(waveRam))
    , waveRamPtr_({ 0xFF30U, false })
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

void GbChannel3::tickApuDiv(const uint8_t frameSequencerStep)
{
  if ((frameSequencerStep % 2U) == 0U) {
    len_.clock();
    if (len_.isRunOut()) {
      disable();
    }
  }
}

void GbChannel3::advanceWaveRam()
{
  auto ramSample = waveRam_->getLocation(waveRamPtr_.address)->getByte();
  if (waveRamPtr_.upper) {
    ramSample >>= HALF_BYTE_SHIFT;
  } else {
    ramSample &= 0b1111U;
  }
  switch ((nr32_->get() >> 5U) & 0b11U) {
  case 0b00U:
    ramSample = 0U;
    break;
  case 0b01U:
    // ramSample >>= 0U;
    break;
  case 0b10U:
    ramSample >>= 1U;
    break;
  case 0b11U:
    ramSample >>= 2U;
    break;
  }
  dac_.set(ramSample);
  if (waveRamPtr_.upper) {
    waveRamPtr_.upper = false;
  } else if (++waveRamPtr_.address > 0xFF3FU) {
    waveRamPtr_.address = 0xFF30U;
    waveRamPtr_.upper = true;
  }
}
