#include "gbobjects.h"

GbObjects::GbObjects(
    OamUP oam, IRegisterAdapterSP lcdc, IRegisterAdapterSP obp1, IRegisterAdapterSP obp2, TileDataUP tileData)
    : oam_(std::move(oam))
    , lcdc_(std::move(lcdc))
    , obp1_(std::move(obp1))
    , obp2_(std::move(obp2))
    , tileData_(std::move(tileData))
{
}

GbObjects::~GbObjects() = default;

void GbObjects::draw(IPixelBuffer& buffer)
{
  for (const auto& obj : oam_->getAll()) {
    if (obj.getX() > 0) {
      const auto tile = tileData_->getTile(obj.getTileIndex());
      for (uint8_t x = 0; x < TileSize; ++x) {
        for (uint8_t y = 0; y < TileSize; ++y) {
          buffer[x + obj.getX()][y + obj.getY()] = tile.get(TilePos { x, y });
        }
      }
    }
  }
}

auto GbObjects::toTileDataIndex(uint8_t objectTileIndex) const -> uint8_t
{ // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  return lcdc_->testBit(ObjSizeBit) ? 0b1111110U & objectTileIndex : objectTileIndex; // TODO: vollständig
}
