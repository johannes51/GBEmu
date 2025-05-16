#include "gbtimer.h"

#include <algorithm>

#include "gbinterrupthandler.h"

GbTimer::GbTimer(DivRegisterSP div, IRegisterAdapter& div_apu, IRegisterAdapter& tima, const IRegisterAdapter& tma,
    const IRegisterAdapter& tac, IRegisterAdapter& ifl)
    : div_(std::move(div))
    , div_apu_(div_apu)
    , tima_(tima)
    , tma_(tma)
    , tac_(tac)
    , if_(ifl)
    , feSystemTimerBit_()
    , feDivApuBit_()
{
}

void GbTimer::clock()
{
  div_->clock();
  if (feSystemTimerBit_.isFallingEdge(div_->testBitSystemTimer(selectPosBit()) && tac_.testBit(TimerEnableBit))) {
    if (tima_.getByte() == TimaMax) {
      if_.setBit(TimerInterruptBit, true);
      tima_.setByte(tma_.getByte());
    } else {
      tima_.setByte(tima_.getByte() + 1);
    }
  }
  if (feDivApuBit_.isFallingEdge(div_->testBitSystemTimer(TimerDivApuBit))) {
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
