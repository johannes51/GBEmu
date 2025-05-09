#ifndef LOCATION16_H
#define LOCATION16_H

#include <cstdint>
#include <memory>

#include "defines.h"

class Location16 {
public:
  virtual ~Location16() = default;
  DISABLE_COPY_AND_MOVE(Location16)

  virtual uint16_t get() const = 0;

  virtual Location16& operator=(const uint16_t& rhs) = 0;

protected:
  explicit Location16() { }
};

using Location16UP = std::unique_ptr<Location16>;

#endif // LOCATION16_H
