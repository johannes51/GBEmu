#include "tilemap.h"

#include "../ppu_constants.h"
#include "helper.h"
#include "location/location8.h"
#include "tiledata.h"

TileMap::TileMap(IRegisterAdapterSP lcdc, IMemoryViewSP mem, uint8_t bit)
    : lcdc_(std::move(lcdc))
    , mem_(std::move(mem))
    , bit_(bit)
{
}

auto TileMap::getIndex(const TileAddress &address) const -> int8_t
{
  return static_cast<int8_t>(mem_->getLocation8(baseAdress() + toFlatAddress(address))->get()); // TODO: unsigned-signed
}

auto TileMap::baseAdress() const -> address_type
{
  return (lcdc_->testBit(bit_) ? TileMapSetBaseAddress : TileMapResetBaseAddress);
}

TileMap::~TileMap() = default;
