#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "mem/mem_defines.h"

constexpr uint16_t UPPER_BYTE_MASK = 0xFF00U;
constexpr uint16_t LOWER_BYTE_MASK = 0x00FFU;
constexpr uint16_t BYTE_MASK = LOWER_BYTE_MASK;
constexpr unsigned BYTE_SHIFT = 8U;

constexpr uint8_t UPPER_NIBBLE_MASK = 0xF0U;
constexpr uint8_t LOWER_NIBBLE_MASK = 0x0FU;
constexpr unsigned NIBBLE_SHIFT = 4U;

constexpr uint16_t BIT_11_MASK = 0b0000111111111111U;
constexpr uint16_t BIT_15_MASK = 0b1111111111111111U;

constexpr unsigned BYTE_BIT_COUNT = 8U;
constexpr uint32_t TWO_BYTE_MASK = 0xFFFFU;
constexpr unsigned TWO_BYTE_BIT_COUNT = 16U;

constexpr address_type ZERO_PAGE_BASE = 0xFF00;

constexpr uint32_t GB_CLOCK = 1048576U;

#endif // CONSTANTS_H
