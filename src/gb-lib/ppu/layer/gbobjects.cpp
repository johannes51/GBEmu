#include "gbobjects.h"

GbObjects::GbObjects(OamUP oam, IRegisterAdapterSP lcdc, IRegisterAdapterSP obp1, IRegisterAdapterSP obp2,
    IRegisterAdapterSP bgp, TileDataUP tileData)
    : oam_(std::move(oam))
    , lcdc_(std::move(lcdc))
    , obp1_(std::move(obp1))
    , obp2_(std::move(obp2))
    , tileData_(std::move(tileData))
    , pal_(std::move(bgp)) // TODO: richtiges register
    , t_(GbColorTransformation::makeGbStdRgb())
{
}

void GbObjects::draw(GbPixelBuffer& buffer, const uint8_t currentLine)
{
  if (!lcdc_->testBit(ObjEnableBit)) {
    return;
  }
  for (const auto& obj : oam_->getAll()) {
    if (obj.getX() > 0) {
      const auto tile = tileData_->getTile(obj.getTileIndex());
      for (uint8_t x = 0; x < TileSize; ++x) {
        buffer.at(x + obj.getX(), currentLine + obj.getY())
            = t_->convert(pal_.getColor(tile.get(TilePos { .x = x, .y = currentLine })));
      }
    }
  }
}

auto GbObjects::toTileDataIndex(uint8_t objectTileIndex) const -> uint8_t
{ // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  return lcdc_->testBit(ObjSizeBit) ? 0b1111110U & objectTileIndex : objectTileIndex; // TODO: vollständig
}
