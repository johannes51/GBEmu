#include "gbpulsechannel.h"

#include "constants.h"

GbPulseChannel::GbPulseChannel(IoBank& io, const address_type registerBaseAddress, IRegisterAdapter& nr52)
    : Channel(nr52)
    , nrX1_()
    , nrX2_()
    , nrX3_()
    , nrX4_()
    , env_(nrX2_)
    , len_(nrX1_, nrX4_)
    , period_(nrX3_, nrX4_)
{
  io.registerRegister(registerBaseAddress + 1U, &nrX1_);
  io.registerRegister(registerBaseAddress + 2U, &nrX2_);
  io.registerRegister(registerBaseAddress + 3U, &nrX3_);
  io.registerRegister(registerBaseAddress + 4U, &nrX4_);
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

void GbPulseChannel::updateWaveform() { selectedTable_ = (nrX1_.getByte() >> WaveFormBit); }
