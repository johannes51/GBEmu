#include "gbtimer.h"

#include <algorithm>

#include "gbinterrupthandler.h"

constexpr address_type TimaAddress = 0xFF05U;
constexpr address_type TmaAddress = 0xFF06U;
constexpr address_type TacAddress = 0xFF07U;
constexpr uint8_t TacInitial = 0xF8U;

GbTimer::GbTimer(IoBank& io, IRegisterAdapter& div_apu, IRegisterAdapter& rIf)
    : div_()
    , div_apu_(div_apu)
    , tima_()
    , tma_()
    , tac_(TacInitial)
    , if_(rIf)
    , feSystemTimerBit_()
    , feDivApuBit_()
{
  io.registerRegister(DivRegisterAddress, &div_);
  io.registerRegister(TimaAddress, &tima_);
  io.registerRegister(TmaAddress, &tma_);
  io.registerRegister(TacAddress, &tac_);
}

void GbTimer::clock()
{
  div_.clock();
  if (feSystemTimerBit_.isFallingEdge(div_.testBitSystemTimer(selectPosBit()) && tac_.testBit(TimerEnableBit))) {
    if (tima_.getByte() == TimaMax) {
      if_.setBit(TimerInterruptBit, true);
      tima_.setByte(tma_.getByte());
    } else {
      tima_.setByte(tima_.getByte() + 1);
    }
  }
  if (feDivApuBit_.isFallingEdge(div_.testBitSystemTimer(TimerDivApuBit))) {
    div_apu_.setByte(div_apu_.getByte() + 1U);
  }
}

auto GbTimer::selectPosBit() const -> uint8_t
{
  const auto& it = std::find_if(ClockSelectBitMap.begin(), ClockSelectBitMap.end(),
      [&](const auto& elem) { return elem.first == (tac_.getByte() & TacClockSelectMask); });
  if (it != ClockSelectBitMap.end()) {
    return it->second;
  } else {
    throw std::logic_error("Should be unreachable.");
  }
}
