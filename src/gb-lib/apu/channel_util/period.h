#ifndef PERIOD_H
#define PERIOD_H

#include <cstdint>

#include "mem/registers/iregisteradapter.h"

class Period {
public:
  Period(const IRegisterAdapter& nrX3, const IRegisterAdapter& nrX4);

  bool clockIsDone();

  void load();

private:
  const IRegisterAdapter& nrX3_;
  const IRegisterAdapter& nrX4_;

  uint16_t period_;

  static constexpr uint8_t PeriodMsbCount = 3U;
  static constexpr uint16_t MaxPeriod = 2048U;
};

#endif // PERIOD_H
