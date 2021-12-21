#include "tilemap.h"

#include "location/location.h"
#include "tiledata.h"

TileMap::TileMap(IRegisterAdapterSP lcdc, IMemoryViewSP mem, std::unique_ptr<TileData> tiles, uint8_t bit)
    : lcdc_(std::move(lcdc))
    , mem_(std::move(mem))
    , tiles_(std::move(tiles))
    , bit_(bit)
{
}

auto TileMap::getTile(const TileAddress& address) -> Tile { return tiles_->getTile(getIndex(toFlatAddress(address))); }

auto TileMap::toFlatAddress(const TileAddress& address) -> uint8_t { return address.x * 32 + address.y; }

auto TileMap::getIndex(uint8_t flatAddress) const -> uint8_t { return mem_->getByte(baseAdress() + flatAddress).get(); }

auto TileMap::baseAdress() const -> address_type { return (lcdc_->testBit(bit_) ? 0x9C00 : 0x9800); }

TileMap::~TileMap() = default;
