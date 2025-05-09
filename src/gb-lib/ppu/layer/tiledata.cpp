#include "tiledata.h"

#include "../ppu_constants.h"

TileData::TileData(IRegisterAdapterSP lcdc, IMemoryViewSP mem, int8_t bit /* = -1*/)
    : lcdc_(std::move(lcdc))
    , mem_(std::move(mem))
    , Bit_(bit)
{
}

auto TileData::getTile(int16_t index) -> Tile { return Tile { loadTile(baseAdress() + TileDataSize * index) }; }

auto TileData::baseAdress() const -> address_type
{
  return (Bit_ < 0 || lcdc_->testBit(Bit_)) ? TileDataSetBaseAddress : TileDataResetBaseAddress;
}

auto TileData::loadTile(address_type address) const -> std::array<uint8_t, TileDataSize>
{
  std::array<uint8_t, TileDataSize> result {};
  for (uint8_t i = 0; i < TileDataSize; ++i) {
    result[i] = mem_->getLocation8(address + i)->get();
  }
  return result;
}
