#ifndef PERIOD_H
#define PERIOD_H

#include <cstdint>

#include "mem/registers/iregisteradapter.h"

class Period {
public:
  Period(IRegisterAdapterSP nrX3, IRegisterAdapterSP nrX4);

  bool clockIsDone();

  void load();

private:
  IRegisterAdapterSP nrX3_;
  IRegisterAdapterSP nrX4_;

  uint16_t period_;

  static constexpr uint8_t PeriodMsbCount = 3U;
  static constexpr uint16_t MaxPeriod = 2048U;
};

#endif // PERIOD_H
