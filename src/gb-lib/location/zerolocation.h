#ifndef ZEROLOCATION_H
#define ZEROLOCATION_H

#include "location16.h"
#include "location8.h"

class ZeroLocation8 final : public Location8 {
public:
  ZeroLocation8()
      : Location8()
  {
  }
  DISABLE_COPY_AND_MOVE(ZeroLocation8)

  const uint8_t& get() const override;
  ZeroLocation8& operator=(const uint8_t& rhs) override;

private:
  static uint8_t zero_;
};

class ZeroLocation16 final : public Location16 {
public:
  ZeroLocation16()
      : Location16()
  {
  }
  DISABLE_COPY_AND_MOVE(ZeroLocation16)

  uint16_t get() const override;
  ZeroLocation16& operator=(const uint16_t& rhs) override;

private:
  static uint16_t zero_;
};

#endif // ZEROLOCATION_H
