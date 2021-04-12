#ifndef HELPERS_H
#define HELPERS_H

#include "location/location.h"
#include "mem/mem_defines.h"

namespace hlp {

constexpr address_type ZeroPageBase = 0xFF00;

address_type indirect(const Location<address_type>& location);
address_type indirect(const Location<uint8_t>& location);

constexpr void setBit(uint8_t& value, uint8_t pos) { value |= (1ULL << pos); }

constexpr void clearBit(uint8_t& value, uint8_t pos) { value &= ~(1ULL << pos); }

constexpr auto checkBit(const uint8_t& value, uint8_t pos) -> bool { return (value & (1U << pos)) != 0; }

constexpr uint8_t MaxBit = 7;
constexpr uint8_t MinBit = 0;

} // namespace hlp

#endif // HELPERS_H
