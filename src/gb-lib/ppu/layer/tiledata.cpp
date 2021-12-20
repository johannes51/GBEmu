#include "tiledata.h"

#include "location/location.h"

TileData::TileData(IRegisterAdapterSP lcdc, IMemoryViewSP mem)
    : lcdc_(std::move(lcdc))
    , mem_(std::move(mem))
{
}

auto TileData::getTile(uint8_t index) -> Tile { return Tile { loadTile(baseAdress() + 2 * index) }; }

auto TileData::baseAdress() const -> address_type { return (lcdc_->testBit(4) ? 0x8000 : 0x8800); }

std::array<uint8_t, 16> TileData::loadTile(address_type address) const
{
  std::array<uint8_t, 16> result;
  for (uint8_t i = 0; i < 16; ++i) {
    result[i] = mem_->getByte(address + i).get();
  }
  return result;
}
