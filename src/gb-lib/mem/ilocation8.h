#ifndef ILOCATION8_H
#define ILOCATION8_H

#include <cstdint>

#include "defines.h"

class ILocation8 {
public:
  DISABLE_COPY_AND_MOVE(ILocation8)
  virtual ~ILocation8() = default;

  virtual const uint8_t& get() const = 0;
  virtual ILocation8& operator=(const uint8_t& rhs) = 0;

protected:
  ILocation8() = default;
};

#endif // ILOCATION8_H
