#include "location.h"

// NOLINTNEXTLINE(modernize-use-trailing-return-type) already is, doesn't recognize
template <> auto Location<uint8_t>::get() const -> uint8_t { return getByte(); }

// NOLINTNEXTLINE(modernize-use-trailing-return-type) already is, doesn't recognize
template <> auto Location<uint16_t>::get() const -> uint16_t { return getWord(); }

template <> void Location<uint8_t>::set(const uint8_t& value) { setByte(value); }

template <> void Location<uint16_t>::set(const uint16_t& value) { setWord(value); }

// NOLINTNEXTLINE(modernize-use-trailing-return-type) already is, doesn't recognize
template <> auto Location<uint8_t>::fuse(Location<uint8_t> lower, Location<uint8_t> upper) -> Location<uint16_t>
{
  return Location<uint16_t>::generate(std::move(lower.lower_), std::move(upper.lower_));
}
