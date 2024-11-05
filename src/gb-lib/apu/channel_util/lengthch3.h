#ifndef LENGTHCH3_H
#define LENGTHCH3_H

#include <cstdint>

#include "mem/registers/iregisteradapter.h"

class LengthCh3 {
public:
  LengthCh3(IRegisterAdapterSP nr31, IRegisterAdapterSP nr34);

  void clock();
  bool isRunOut() const;

private:
  enum LENGTH_COUNTER : uint16_t {
    LEN_MAX_VAL = 0x00FFU,
    LEN_STOPPED = 0x10FFU,
    LEN_INACTIVE = 0x11FFU,
  };

  static constexpr uint8_t LenEnableBitPos = 6U;

  IRegisterAdapterSP nr31_;
  IRegisterAdapterSP nr34_;

  uint16_t counter_ = LEN_INACTIVE;

  void checkEnable();
  void setCounter();
};

#endif // LENGTHCH3_H
