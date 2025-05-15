#ifndef PPU_CONSTANTS_H
#define PPU_CONSTANTS_H

#include <cstdint>

#include "mem/mem_defines.h"

// General display constants
constexpr uint16_t DotsPerCycles = 4U;
constexpr uint16_t LcdWidth = 160U;
constexpr uint16_t LcdHeight = 144U;
constexpr uint16_t LcdWithVBlankHeight = 154U;
constexpr uint16_t CyclesPerLine = LcdWidth / DotsPerCycles;
constexpr uint16_t CyclesPerFrame = CyclesPerLine * LcdWithVBlankHeight;
constexpr uint16_t Mode2Length = 80U;
constexpr uint16_t Mode3MaxLength = 289U;

// LCDC Bits
constexpr uint8_t BgWindowEnablePrioBit = 0U;
constexpr uint8_t ObjEnableBit = 1U;
constexpr uint8_t ObjSizeBit = 2U;
constexpr uint8_t BgTileMapBit = 3U;
constexpr uint8_t BgWindowTileDataBit = 4U;
constexpr uint8_t WindowEnableBit = 5U;
constexpr uint8_t WindowTileMapBit = 6U;
constexpr uint8_t LcdEnableBit = 7U;

// STAT Bits
constexpr uint8_t PpuModeLowerBit = 0U;
constexpr uint8_t PpuModeHigherBit = 1U;
constexpr uint8_t LycLyCompareBit = 2U;
constexpr uint8_t Mode0IntBit = 3U;
constexpr uint8_t Mode1IntBit = 4U;
constexpr uint8_t Mode2IntBit = 5U;
constexpr uint8_t LycIntBit = 6U;

// OAM Bits
constexpr uint8_t PalleteBit = 4U;
constexpr uint8_t FlipXBit = 5U;
constexpr uint8_t FlipYBit = 6U;
constexpr uint8_t PriorityBit = 7U;

// Tile Data constants
constexpr uint16_t TileSize = 8U;
constexpr uint8_t TileMapSize = 32U;
constexpr uint16_t TileMapWidth = 256U;
constexpr uint16_t TileMapHeight = 256U;
constexpr std::size_t TileDataSize = 16U;
constexpr address_type TileDataSetBaseAddress = 0x8000U;
constexpr address_type TileDataResetBaseAddress = 0x8800U;
constexpr address_type TileMapSetBaseAddress = 0x9C00U;
constexpr address_type TileMapResetBaseAddress = 0x9800U;

#endif // PPU_CONSTANTS_H
