#ifndef LENGTH_H
#define LENGTH_H

#include <cstdint>

#include "mem/registers/iregisteradapter.h"

class Length {
public:
  Length(IRegisterAdapterSP nrX1, IRegisterAdapterSP nrX4);

  void clock();
  bool isRunOut() const;

private:
  enum LENGTH_COUNTER : uint8_t {
    LEN_MAX_VAL = 0b01000000U,
    LEN_STOPPED = 0b10000000U,
    LEN_INACTIVE = 0b10000001U,
  };

  static constexpr uint8_t LenEnableBitPos = 6U;
  static constexpr uint8_t CounterMask = 0b111111U;

  IRegisterAdapterSP nrX1_;
  IRegisterAdapterSP nrX4_;

  uint8_t counter_ = LEN_INACTIVE;

  void checkEnable();
  void setCounter();
};

#endif // LENGTH_H
