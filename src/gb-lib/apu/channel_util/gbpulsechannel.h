#ifndef GBPULSECHANNEL_H
#define GBPULSECHANNEL_H

#include "../channel.h"

#include <array>

#include "envelope.h"
#include "io/fixedmaskioregister.h"
#include "io/iobank.h"
#include "io/ioregister.h"
#include "length.h"
#include "period.h"

class GbPulseChannel : public Channel {
public:
  explicit GbPulseChannel(IoBank& io, const address_type registerBaseAddress, IRegisterAdapter& nr52);

  void clock() override;
  void tickApuDiv(const FrameSequence sequence) override;

protected:
  IoRegister nrX1_;
  IoRegister nrX2_;
  IoRegister nrX3_;
  FixedMaskIoRegister<0b00111000U> nrX4_;

private:
  static constexpr uint8_t DutyWaveformLength = 8U;
  using waveformTable = std::array<uint8_t, DutyWaveformLength>;
  static constexpr uint8_t DutyWaveformCount = 4U;
  using dutyTable = std::array<waveformTable, DutyWaveformCount>;
  static constexpr uint8_t WaveFormBit = 6U;

  static constexpr dutyTable PulseDutyWaveformTable = { { { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U },
      { 0U, 0U, 0U, 0U, 0U, 0U, 1U, 1U }, { 0U, 0U, 0U, 0U, 1U, 1U, 1U, 1U }, { 1U, 1U, 1U, 1U, 1U, 1U, 0U, 0U } } };

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
