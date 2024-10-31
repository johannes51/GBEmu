#include "gbtimer.h"

#include <algorithm>

GbTimer::GbTimer(DivRegisterSP div, IRegisterAdapterSP div_apu, IRegisterAdapterSP tima, IRegisterAdapterSP tma,
    IRegisterAdapterSP tac, IRegisterAdapterSP ifl)
    : div_(std::move(div))
    , div_apu_(std::move(div_apu))
    , tima_(std::move(tima))
    , tma_(std::move(tma))
    , tac_(std::move(tac))
    , if_(std::move(ifl))
    , feSystemTimerBit_()
    , feDivApuBit_()
{
}

void GbTimer::clock()
{
  div_->clock();
  if (feSystemTimerBit_.isFallingEdge(div_->testBitSystemTimer(selectPosBit()) && tac_->testBit(TimerEnableBit))) {
    if (tima_->get() == TimaMax) {
      if_->setBit(TimerInterruptBit, true);
      tima_->set(tma_->get());
    } else {
      tima_->set(tima_->get() + 1);
    }
  }
  if (feDivApuBit_.isFallingEdge(div_->testBitSystemTimer(TimerDivApuBit))) {
    div_apu_->set(div_apu_->get() + 1U);
  }
}

auto GbTimer::selectPosBit() const -> uint8_t
{
  const auto& it = std::find_if(ClockSelectBitMap.begin(), ClockSelectBitMap.end(),
      [&](const auto& elem) { return elem.first == (tac_->get() & TacClockSelectMask); });
  if (it != ClockSelectBitMap.end()) {
    return it->second;
  } else {
    throw std::logic_error("Should be unreachable.");
  }
}
