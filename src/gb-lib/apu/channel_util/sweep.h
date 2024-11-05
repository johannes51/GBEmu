#ifndef SWEEP_H
#define SWEEP_H

#include "mem/registers/iregisteradapter.h"

class Sweep {
public:
  Sweep(IRegisterAdapterSP nr10, IRegisterAdapterSP nr13, IRegisterAdapterSP nr14);

  void clock();

private:
  static constexpr uint8_t StepBitCount = 3U;
  static constexpr uint8_t DirectionBitPos = 3U;
  static constexpr uint8_t CounterPeriodMask = 0b111U;
  static constexpr uint8_t CounterBitPos = 4U;
  static constexpr uint8_t CounterBitCount = 3U;

  IRegisterAdapterSP nr10_;
  IRegisterAdapterSP nr13_;
  IRegisterAdapterSP nr14_;

  uint8_t counter_ = 0U;

  void loadCounter();
  void modifyPeriod();
};

#endif // SWEEP_H
