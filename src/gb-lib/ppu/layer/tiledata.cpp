#include "tiledata.h"

TileData::TileData(IRegisterAdapterSP lcdc, IMemoryViewSP mem, int8_t bit /* = -1*/)
    : lcdc_(std::move(lcdc))
    , mem_(std::move(mem))
    , Bit_(bit)
{
}

auto TileData::getTile(uint8_t index) -> Tile { return Tile { loadTile(baseAdress() + 2 * index) }; }

auto TileData::baseAdress() const -> address_type
{
  return (Bit_ < 0 || lcdc_->testBit(Bit_)) ? SetBaseAddress : ResetBaseAddress;
}

auto TileData::loadTile(address_type address) const -> std::array<uint8_t, 16>
{
  std::array<uint8_t, 16> result;
  for (uint8_t i = 0; i < 16; ++i) {
    result[i] = mem_->getByte(address + i).get();
  }
  return result;
}
