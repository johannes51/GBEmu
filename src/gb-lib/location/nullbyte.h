#ifndef NULLBYTE_H
#define NULLBYTE_H

#include "locationbyte.h"

class NullByte final : public LocationByte {
public:
  NullByte() = default;
  DISABLE_COPY_AND_MOVE(NullByte)

  uint8_t get() const override;
  void set(const uint8_t& value) override;
};

#endif // NULLBYTE_H
