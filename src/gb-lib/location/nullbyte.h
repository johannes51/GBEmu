#ifndef NULLBYTE_H
#define NULLBYTE_H

#include "locationbyte.h"

class NullByte final : public LocationByte {
public:
  NullByte() = default;
  DISABLE_COPY_AND_MOVE(NullByte)

  uint8_t operator*();
  NullByte &operator<<(const uint8_t &value);
};

#endif // NULLBYTE_H
