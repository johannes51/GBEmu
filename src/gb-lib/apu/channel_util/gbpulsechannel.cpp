#include "gbpulsechannel.h"

#include "constants.h"

GbPulseChannel::GbPulseChannel(const IRegisterAdapter& nrX1, const IRegisterAdapter& nrX2, const IRegisterAdapter& nrX3,
    const IRegisterAdapter& nrX4, IRegisterAdapter& nr52)
    : Channel(nr52)
    , nrX1_(nrX1)
    , nrX3_(nrX3)
    , nrX4_(nrX4)
    , env_(nrX2)
    , len_(nrX1, nrX4)
    , period_(nrX3, nrX4)
{
}

void GbPulseChannel::clock()
{
  if (nr52_.testBit(1U)) {
    if (period_.clockIsDone()) {
      updateWaveform();
      tickDuty();
    }
  }
}

void GbPulseChannel::tickApuDiv(const FrameSequence sequence)
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
  case FrameSequence::Phase7:
    env_.clock();
    break;
  default:
    break;
  }
}

void GbPulseChannel::tickDuty()
{
  if (++dutyPosition_ >= DutyWaveformLength) {
    dutyPosition_ = 0U;
  }
  updateSample();
}

void GbPulseChannel::updateSample() { dac_.set(PulseDutyWaveformTable[selectedTable_][dutyPosition_] * env_.vol()); }

void GbPulseChannel::updateWaveform() { selectedTable_ = (nrX1_.getByte() >> WaveFormBitPos); }
