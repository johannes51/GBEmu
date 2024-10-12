#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "mem/mem_defines.h"

constexpr unsigned int MASK_UPPER_BYTE = 0xFF00U;
constexpr unsigned int MASK_LOWER_BYTE = 0x00FFU;

constexpr unsigned int MASK_UPPER_HALF_BYTE = 0xF0U;
constexpr unsigned int MASK_LOWER_HALF_BYTE = 0x0FU;

constexpr unsigned int BYTE_SHIFT = 8U;
constexpr unsigned int HALF_BYTE_SHIFT = 4U;

constexpr address_type ZERO_PAGE_BASE = 0xFF00;

#endif // CONSTANTS_H
