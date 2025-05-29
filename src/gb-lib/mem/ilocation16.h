#ifndef ILOCATION16_H
#define ILOCATION16_H

#include <cstdint>

#include "defines.h"

class ILocation16 {
public:
  DISABLE_COPY_AND_MOVE(ILocation16)
  virtual ~ILocation16() = default;

  virtual const uint16_t& get() const = 0;
  virtual ILocation16& operator=(const uint16_t& rhs) = 0;

protected:
  ILocation16() = default;
};

#endif // ILOCATION16_H
