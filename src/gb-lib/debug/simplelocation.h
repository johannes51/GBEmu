#ifndef SIMPLELOCATION_H
#define SIMPLELOCATION_H

#include "location/locationbyte.h"

class SimpleLocation final : public LocationByte {
public:
  SimpleLocation() = default;
  DISABLE_COPY_AND_MOVE(SimpleLocation)

  uint8_t get() const override;
  void set(const uint8_t &value) override;
};

#endif // SIMPLELOCATION_H
