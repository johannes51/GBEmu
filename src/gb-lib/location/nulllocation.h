#ifndef NULLLOCATION_H
#define NULLLOCATION_H

#include "location8.h"

class NullLocation final : public Location8 {
public:
  NullLocation();
  DISABLE_COPY_AND_MOVE(NullLocation)

  const uint8_t& get() const override;
  NullLocation& operator=(const uint8_t& rhs) override;
};

#endif // NULLLOCATION_H
