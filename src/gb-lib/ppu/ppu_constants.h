#ifndef PPU_CONSTANTS_H
#define PPU_CONSTANTS_H

#include <cstdint>

#include "mem/mem_defines.h"

// LCDC Bits
constexpr uint8_t ObjSizeBit = 2;
constexpr uint8_t BgTileMapBit = 3;
constexpr uint8_t BgWindowTileDataBit = 4;
constexpr uint8_t WindowTileMapBit = 6;

// OAM Bits
constexpr uint8_t PalleteBit = 4;
constexpr uint8_t FlipXBit = 5;
constexpr uint8_t FlipYBit = 6;
constexpr uint8_t PriorityBit = 7;

constexpr uint8_t LcdWidth = 160;
constexpr uint8_t LcdHeight = 144;
constexpr uint8_t TileSize = 8;
constexpr uint8_t TileMapSize = 32;
constexpr std::size_t TileDataSize = 16;
constexpr address_type TileDataSetBaseAddress = 0x8000;
constexpr address_type TileDataResetBaseAddress = 0x8800;
constexpr address_type TileMapSetBaseAddress = 0x9C00;
constexpr address_type TileMapResetBaseAddress = 0x9800;

#endif // PPU_CONSTANTS_H
