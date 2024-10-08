#ifndef HELPERS_H
#define HELPERS_H

#include "location/location.h"
#include "mem/mem_defines.h"

namespace hlp {

constexpr address_type ZeroPageBase = 0xFF00;

template <typename T> address_type indirect(const T& location) { return location.getWord(); }

address_type indirectZeroPage(const Location& location);

constexpr void setBit(uint8_t& value, uint8_t pos) { value |= (1U << pos); }

constexpr void clearBit(uint8_t& value, uint8_t pos) { value &= ~(1U << pos); }

constexpr auto checkBit(const uint8_t& value, uint8_t pos) -> bool { return (value & (1U << pos)) != 0; }

constexpr uint8_t MaxBit = 7;
constexpr uint8_t MinBit = 0;

} // namespace hlp

#endif // HELPERS_H
