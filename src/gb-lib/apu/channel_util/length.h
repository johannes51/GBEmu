#ifndef LENGTH_H
#define LENGTH_H

#include <cstdint>

#include "io/iregisteradapter.h"

class Length {
public:
  Length(const IRegisterAdapter& nrX1, const IRegisterAdapter& nrX4);

  void clock();
  bool isRunOut() const;

private:
  void checkEnable();
  void setCounter();

  enum LENGTH_COUNTER : uint8_t {
    LEN_MAX_VAL = 0b01000000U,
    LEN_STOPPED = 0b10000000U,
    LEN_INACTIVE = 0b10000001U,
  };

  static constexpr uint8_t LenEnableBit = 6U;
  static constexpr uint8_t CounterMask = 0b111111U;

  const IRegisterAdapter& nrX1_;
  const IRegisterAdapter& nrX4_;

  uint8_t counter_ = LEN_INACTIVE;
};

#endif // LENGTH_H
