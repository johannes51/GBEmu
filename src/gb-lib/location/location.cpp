#include "location.h"

template <> uint8_t Location<uint8_t>::get() const { return getByte(); }

template <> uint16_t Location<uint16_t>::get() const { return getWord(); }

template <>
void Location<uint8_t>::set(const uint8_t &value) {
  setByte(value);
}

template <>
void Location<uint16_t>::set(const uint16_t &value) {
  setWord(value);
}
