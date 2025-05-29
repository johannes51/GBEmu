#ifndef GBTIMER_H
#define GBTIMER_H

#include "tickable.h"

#include <array>

#include "io/divregister.h"
#include "io/ioregister.h"
#include "util/fallingedgedetector.h"

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
  explicit GbTimer(IoBank& io, IRegisterAdapter& div_apu, IRegisterAdapter& rIf);
  DISABLE_COPY_AND_MOVE(GbTimer)
  ~GbTimer() override = default;

  IRegisterAdapter* getDiv() { return &div_; }
  IRegisterAdapter* getTma() { return &tma_; }
  IRegisterAdapter* getTima() { return &tima_; }
  IRegisterAdapter* getTac() { return &tac_; }

  void clock() override;

private:
  DivRegister div_;
  IRegisterAdapter& div_apu_;
  IoRegister tima_;
  IoRegister tma_;
  IoRegister tac_;
  IRegisterAdapter& if_;

  FallingEdgeDetector<bool, false> feSystemTimerBit_;
  FallingEdgeDetector<bool, false> feDivApuBit_;

  uint8_t selectPosBit() const;
};

#endif // GBTIMER_H
