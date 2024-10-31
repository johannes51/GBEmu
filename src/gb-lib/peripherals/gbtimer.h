#ifndef GBTIMER_H
#define GBTIMER_H

#include "tickable.h"

#include <array>

#include "mem/registers/divregister.h"
#include "mem/registers/iregisteradapter.h"
#include "util/fallingedgedetector.h"

constexpr uint8_t TimerInterruptBit = 2U;
constexpr uint8_t TimerEnableBit = 2U;
constexpr uint8_t TimerDivApuBit = 10U;
constexpr uint8_t TimaMax = 0xFFU;
constexpr uint8_t TacClockSelectMask = 0b11U;

constexpr std::array<std::pair<uint8_t, uint8_t>, 4U> ClockSelectBitMap = {
  std::make_pair(0b00U, 7U),
  std::make_pair(0b01U, 1U),
  std::make_pair(0b10U, 3U),
  std::make_pair(0b11U, 5U),
};

class GbTimer : public Tickable {
public:
  GbTimer(DivRegisterSP div, IRegisterAdapterSP div_apu, IRegisterAdapterSP tima, IRegisterAdapterSP tma,
      IRegisterAdapterSP tac, IRegisterAdapterSP ifl);

  void clock() override;

private:
  DivRegisterSP div_;
  IRegisterAdapterSP div_apu_;
  IRegisterAdapterSP tima_;
  IRegisterAdapterSP tma_;
  IRegisterAdapterSP tac_;
  IRegisterAdapterSP if_;

  FallingEdgeDetector<bool, false> feSystemTimerBit_;
  FallingEdgeDetector<bool, false> feDivApuBit_;

  uint8_t selectPosBit() const;
};

#endif // GBTIMER_H
