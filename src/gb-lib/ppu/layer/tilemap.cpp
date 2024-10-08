#include "tilemap.h"

#include "../ppu_constants.h"
#include "location/location.h"
#include "tiledata.h"

TileMap::TileMap(IRegisterAdapterSP lcdc, IMemoryViewSP mem, TileDataUP tiles, uint8_t bit)
    : lcdc_(std::move(lcdc))
    , mem_(std::move(mem))
    , tiles_(std::move(tiles))
    , bit_(bit)
{
}

auto TileMap::getTile(const TileAddress& address) -> Tile { return tiles_->getTile(getIndex(toFlatAddress(address))); }

auto TileMap::toFlatAddress(const TileAddress& address) -> uint8_t { return address.x * TileMapSize + address.y; }

auto TileMap::getIndex(uint8_t flatAddress) const -> int8_t
{
  return static_cast<int8_t>(mem_->getLocation(baseAdress() + flatAddress)->getByte()); // TODO: unsigned-signed
}

auto TileMap::baseAdress() const -> address_type
{
  return (lcdc_->testBit(bit_) ? TileMapSetBaseAddress : TileMapResetBaseAddress);
}

TileMap::~TileMap() = default;
