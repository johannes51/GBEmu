#ifndef HELPERS_H
#define HELPERS_H

#include "constants.h"
#include "mem/location16.h"
#include "mem/location8.h"
#include "mem/mem_defines.h"

namespace hlp {

address_type indirect(const Location16& location);

address_type indirectZeroPage(const Location8& location);

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
  if (len > BYTE_BIT_COUNT) {
    throw std::invalid_argument("cannot shift by more bits than are available");
  }
  auto result = value;
  result >>= start;
  result &= (BYTE_MASK >> (BYTE_BIT_COUNT - len));
  return result;
}
constexpr auto getBits(const uint16_t& value, uint8_t start, uint8_t len) -> uint16_t
{
  if (len > TWO_BYTE_BIT_COUNT) {
    throw std::invalid_argument("cannot shift by more bits than are available");
  }
  auto result = value;
  result >>= start;
  result &= (TWO_BYTE_MASK >> (TWO_BYTE_BIT_COUNT - len));
  return result;
}

constexpr uint8_t MaxBit = 7;
constexpr uint8_t MinBit = 0;

} // namespace hlp

#endif // HELPERS_H
