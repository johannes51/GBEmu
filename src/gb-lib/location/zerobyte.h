#ifndef ZEROBYTE_H
#define ZEROBYTE_H

#include "locationbyte.h"

class ZeroByte final : public LocationByte {
public:
  ZeroByte() = default;
  DISABLE_COPY_AND_MOVE(ZeroByte)

  uint8_t get() const override;
  void set(const uint8_t& value) override;
};

#endif // ZEROBYTE_H
