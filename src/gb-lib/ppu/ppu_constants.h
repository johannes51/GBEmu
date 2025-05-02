#ifndef PPU_CONSTANTS_H
#define PPU_CONSTANTS_H

#include <cstdint>

#include "mem/mem_defines.h"

// General display constants
constexpr uint16_t DotsPerCycles = 4U;
constexpr uint8_t LcdWidth = 160U;
constexpr uint8_t LcdHeight = 144U;
constexpr uint8_t LcdWithVBlankHeight = 154U;
constexpr uint16_t CyclesPerLine = LcdWidth / DotsPerCycles;
constexpr uint16_t CyclesPerFrame = CyclesPerLine * LcdWithVBlankHeight;

// LCDC Bits
constexpr uint8_t BgWindowEnablePrioBit = 0U;
constexpr uint8_t ObjEnableBit = 1U;
constexpr uint8_t ObjSizeBit = 2U;
constexpr uint8_t BgTileMapBit = 3U;
constexpr uint8_t BgWindowTileDataBit = 4U;
constexpr uint8_t WindowEnableBit = 5U;
constexpr uint8_t WindowTileMapBit = 6U;
constexpr uint8_t LcdEnableBit = 7U;

// OAM Bits
constexpr uint8_t PalleteBit = 4U;
constexpr uint8_t FlipXBit = 5U;
constexpr uint8_t FlipYBit = 6U;
constexpr uint8_t PriorityBit = 7U;

// Tile Data constants
constexpr uint8_t TileSize = 8U;
constexpr uint8_t TileMapSize = 32U;
constexpr std::size_t TileDataSize = 16U;
constexpr address_type TileDataSetBaseAddress = 0x8000U;
constexpr address_type TileDataResetBaseAddress = 0x8800U;
constexpr address_type TileMapSetBaseAddress = 0x9C00U;
constexpr address_type TileMapResetBaseAddress = 0x9800U;

#endif // PPU_CONSTANTS_H
