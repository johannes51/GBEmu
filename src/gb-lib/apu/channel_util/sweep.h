#ifndef SWEEP_H
#define SWEEP_H

#include "mem/registers/iregisteradapter.h"

class Sweep {
public:
  Sweep(const IRegisterAdapter& nr10, IRegisterAdapter& nr13, IRegisterAdapter& nr14);

  void clock();

private:
  static constexpr uint8_t StepBitCount = 3U;
  static constexpr uint8_t DirectionBit = 3U;
  static constexpr uint8_t CounterPeriodMask = 0b111U;
  static constexpr uint8_t CounterBit = 4U;
  static constexpr uint8_t CounterBitCount = 3U;

  const IRegisterAdapter& nr10_;
  IRegisterAdapter& nr13_;
  IRegisterAdapter& nr14_;

  uint8_t counter_ = 0U;

  void loadCounter();
  void modifyPeriod();
};

#endif // SWEEP_H
