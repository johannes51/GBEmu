#include "gbpulsechannel.h"

#include "constants.h"

GbPulseChannel::GbPulseChannel(IRegisterAdapterSP nrX1, IRegisterAdapterSP nrX2, IRegisterAdapterSP nrX3,
    IRegisterAdapterSP nrX4, IRegisterAdapterSP nr52)
    : Channel(std::move(nr52))
    , nrX1_(nrX1)
    , nrX3_(nrX3)
    , nrX4_(nrX4)
    , env_(std::move(nrX2))
    , len_(std::move(nrX1), nrX4)
    , period_(std::move(nrX3), std::move(nrX4))
{
  if (!nrX1_ || !nrX3_ || !nrX4_) {
    throw std::invalid_argument("Audio registers not set."); // NOTE: unreachable
  }
}

void GbPulseChannel::clock()
{
  if (nr52_->testBit(1U)) {
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

void GbPulseChannel::updateWaveform() { selectedTable_ = (nrX1_->get() >> WaveFormBitPos); }
