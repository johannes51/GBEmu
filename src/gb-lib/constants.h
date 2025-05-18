#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "mem/mem_defines.h"

constexpr unsigned int UPPER_BYTE_MASK = 0xFF00U;
constexpr unsigned int LOWER_BYTE_MASK = 0x00FFU;

constexpr unsigned int UPPER_HALF_BYTE_MASK = 0xF0U;
constexpr unsigned int LOWER_HALF_BYTE_MASK = 0x0FU;

constexpr unsigned int BIT_11_MASK = 0b0000111111111111U;
constexpr unsigned int BIT_15_MASK = 0b1111111111111111U;

constexpr unsigned int BYTE_SHIFT = 8U;
constexpr unsigned int HALF_BYTE_SHIFT = 4U;

constexpr unsigned int BYTE_MASK = 0xFFU;
constexpr unsigned int BYTE_BIT_COUNT = 8U;
constexpr unsigned int TWO_BYTE_MASK = 0xFFFFU;
constexpr unsigned int TWO_BYTE_BIT_COUNT = 16U;

constexpr address_type ZERO_PAGE_BASE = 0xFF00;

constexpr uint32_t GB_CLOCK = 1048576U;

#endif // CONSTANTS_H
