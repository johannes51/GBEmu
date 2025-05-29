#ifndef ZEROLOCATION_H
#define ZEROLOCATION_H

#include "../ilocation8.h"

#include "defines.h"

class ZeroLocation final : public ILocation8 {
public:
  ZeroLocation() = default;
  DISABLE_COPY_AND_MOVE(ZeroLocation)
  ~ZeroLocation() override = default;

  const uint8_t& get() const override { return zero_; }
  ILocation8& operator=(const uint8_t& rhs) override
  {
    (void)rhs;
    return *this;
  }

private:
  static constexpr uint8_t zero_ = { 0U };
};

#endif // ZEROLOCATION_H
