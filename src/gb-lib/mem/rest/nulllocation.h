#ifndef NULLLOCATION_H
#define NULLLOCATION_H

#include "../bytelocationadapter.h"
#include "defines.h"

class NullLocation final : public ByteLocationAdapter {
public:
  NullLocation() = default;
  DISABLE_COPY_AND_MOVE(NullLocation)

  const uint8_t& get() const override;
  void set(const uint8_t& value) override;
};

#endif // NULLLOCATION_H
