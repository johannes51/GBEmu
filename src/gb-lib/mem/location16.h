#ifndef LOCATION16_H
#define LOCATION16_H

#include <cstdint>

#include "defines.h"
#include "wordlocationadapter.h"

class Location16 final {
public:
  Location16()
      : Location16(nullptr)
  {
  }
  Location16(WordLocationAdapterUP adapter)
      : adapter_(std::move(adapter))
  {
  }

  virtual ~Location16() = default;
  DISABLE_COPY(Location16)
  Location16(Location16&&) = default;
  Location16& operator=(Location16&&) = default;

  uint16_t get() const { return adapter_->get(); }
  Location16& operator=(const uint16_t& rhs)
  {
    adapter_->set(rhs);
    return *this;
  }

private:
  WordLocationAdapterUP adapter_;
};

#endif // LOCATION16_H
