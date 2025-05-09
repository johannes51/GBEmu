#ifndef LOCATION8_H
#define LOCATION8_H

#include <cstdint>
#include <memory>

#include "defines.h"

class Location8 {
public:
  virtual ~Location8() = default;
  DISABLE_COPY_AND_MOVE(Location8)

  virtual const uint8_t& get() const = 0;

  virtual Location8& operator=(const uint8_t& rhs) = 0;

protected:
  explicit Location8() { }
};

using Location8UP = std::unique_ptr<Location8>;

#endif // LOCATION8_H
