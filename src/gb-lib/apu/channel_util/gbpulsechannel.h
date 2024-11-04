#ifndef GBPULSECHANNEL_H
#define GBPULSECHANNEL_H

#include "../channel.h"

#include <array>

#include "envelope.h"
#include "length.h"
#include "period.h"

class GbPulseChannel : public Channel {
public:
  GbPulseChannel(IRegisterAdapterSP nrX1, IRegisterAdapterSP nrX2, IRegisterAdapterSP nrX3, IRegisterAdapterSP nrX4,
      IRegisterAdapterSP nr52);

  void clock() override;
  void tickApuDiv(const uint8_t frameSequencerStep) override;

private:
  static constexpr uint8_t DutyWaveformLength = 8U;
  using waveformTable = std::array<uint8_t, DutyWaveformLength>;
  static constexpr uint8_t DutyWaveformCount = 4U;
  using dutyTable = std::array<waveformTable, DutyWaveformCount>;

  static constexpr dutyTable PulseDutyWaveformTable = { { { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U },
      { 0U, 0U, 0U, 0U, 0U, 0U, 1U, 1U }, { 0U, 0U, 0U, 0U, 1U, 1U, 1U, 1U }, { 1U, 1U, 1U, 1U, 1U, 1U, 0U, 0U } } };

  IRegisterAdapterSP nrX1_;
  IRegisterAdapterSP nrX3_;
  IRegisterAdapterSP nrX4_;

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
