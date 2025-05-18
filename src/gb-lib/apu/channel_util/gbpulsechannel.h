#ifndef GBPULSECHANNEL_H
#define GBPULSECHANNEL_H

#include "../channel.h"

#include <array>

#include "envelope.h"
#include "length.h"
#include "period.h"

class GbPulseChannel : public Channel {
public:
  GbPulseChannel(const IRegisterAdapter& nrX1, const IRegisterAdapter& nrX2, const IRegisterAdapter& nrX3,
      const IRegisterAdapter& nrX4, IRegisterAdapter& nr52);

  void clock() override;
  void tickApuDiv(const FrameSequence sequence) override;

private:
  static constexpr uint8_t DutyWaveformLength = 8U;
  using waveformTable = std::array<uint8_t, DutyWaveformLength>;
  static constexpr uint8_t DutyWaveformCount = 4U;
  using dutyTable = std::array<waveformTable, DutyWaveformCount>;
  static constexpr uint8_t WaveFormBit = 6U;

  static constexpr dutyTable PulseDutyWaveformTable = { { { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U },
      { 0U, 0U, 0U, 0U, 0U, 0U, 1U, 1U }, { 0U, 0U, 0U, 0U, 1U, 1U, 1U, 1U }, { 1U, 1U, 1U, 1U, 1U, 1U, 0U, 0U } } };

  const IRegisterAdapter& nrX1_;
  const IRegisterAdapter& nrX3_;
  const IRegisterAdapter& nrX4_;

  Envelope env_;
  Length len_;
  Period period_;

  uint8_t dutyPosition_ = 0U;
  uint8_t frameSequencer_ = 0U;

  uint8_t selectedTable_ = 0b00U;

  void tickDuty();
  void updateSample();
  void loadPeriod();
  void updateWaveform();
};

#endif // GBPULSECHANNEL_H
