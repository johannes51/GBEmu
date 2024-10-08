#ifndef NULLLOCATION_H
#define NULLLOCATION_H

#include "location.h"

class NullLocation final : public Location {
public:
  NullLocation();
  DISABLE_COPY_AND_MOVE(NullLocation)

  const uint8_t& getByte() const override;
  const uint16_t& getWord() const override;
  Location& operator=(const uint8_t& rhs) override;
  Location& operator=(const uint16_t& rhs) override;
};

#endif // NULLLOCATION_H
