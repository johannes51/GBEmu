#ifndef LOCATION8_H
#define LOCATION8_H

#include <cstdint>

#include "bytelocationadapter.h"
#include "defines.h"

class Location8 final {
public:
  DISABLE_COPY(Location8)
  Location8(Location8&&) = default;
  Location8& operator=(Location8&&) = default;

  const uint8_t& get() const { return adapter_->get(); }
  Location8& operator=(const uint8_t& rhs)
  {
    adapter_->set(rhs);
    return *this;
  }

  Location8(ByteLocationAdapterUP adapter)
      : adapter_(std::move(adapter))
  {
  }

private:
  ByteLocationAdapterUP adapter_;
};

#endif // LOCATION8_H
