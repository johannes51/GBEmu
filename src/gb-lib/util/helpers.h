#ifndef HELPERS_H
#define HELPERS_H

#include "location/location.h"
#include "mem/mem_defines.h"

namespace hlp {

template <typename T> address_type indirect(const T& location) { return location.getWord(); }

address_type indirectZeroPage(const Location& location);

constexpr void setBit(uint8_t& value, uint8_t pos) { value |= (1U << pos); }
constexpr void setBit(uint16_t& value, uint8_t pos) { value |= (1U << pos); }

constexpr void clearBit(uint8_t& value, uint8_t pos) { value &= ~(1U << pos); }
constexpr void clearBit(uint16_t& value, uint8_t pos) { value &= ~(1U << pos); }

constexpr void writeBit(uint8_t& value, uint8_t pos, bool set)
{
  if (set) {
    setBit(value, pos);
  } else {
    clearBit(value, pos);
  }
}
constexpr void writeBit(uint16_t& value, uint8_t pos, bool set)
{
  if (set) {
    setBit(value, pos);
  } else {
    clearBit(value, pos);
  }
}

constexpr auto checkBit(const uint8_t& value, uint8_t pos) -> bool { return (value & (1U << pos)) != 0; }
constexpr auto checkBit(const uint16_t& value, uint8_t pos) -> bool { return (value & (1U << pos)) != 0; }

constexpr auto getBits(const uint8_t& value, uint8_t start, uint8_t len) -> uint8_t
{
  auto result = value;
  result >>= start;
  result &= (0xFFU >> (8U - len));
  return result;
}
constexpr auto getBits(const uint16_t& value, uint8_t start, uint8_t len) -> uint16_t
{
  auto result = value;
  result >>= start;
  result &= (0xFFFFU >> (16U - len));
  return result;
}

constexpr uint8_t MaxBit = 7;
constexpr uint8_t MinBit = 0;

} // namespace hlp

#endif // HELPERS_H
