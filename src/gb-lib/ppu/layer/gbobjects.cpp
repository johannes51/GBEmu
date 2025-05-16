#include "gbobjects.h"

GbObjects::GbObjects(OamUP oam, const IRegisterAdapter& lcdc, const IRegisterAdapter& obp1,
    const IRegisterAdapter& obp2, const IRegisterAdapter& bgp, TileDataUP tileData)
    : oam_(std::move(oam))
    , lcdc_(lcdc)
    , obp1_(obp1)
    , obp2_(obp2)
    , tileData_(std::move(tileData))
    , pal_(bgp) // TODO: richtiges register
    , t_(GbColorTransformation::makeGbStdRgb())
{
}

void GbObjects::draw(GbPixelBuffer& buffer, const uint8_t currentLine)
{
  if (!lcdc_.testBit(ObjEnableBit)) {
    return;
  }
  for (const auto& obj : oam_->getAll()) {
    if (obj.getX() > 0) {
      const auto tile = tileData_->getTile(obj.getTileIndex());
      const auto currentTileLine = (obj.getY() + ObjVertOffset) - currentLine;
      if (currentTileLine >= 0 && currentTileLine < TileSize) {
        for (uint8_t x = 0; x < TileSize; ++x) {
          buffer.at(x + obj.getX(), currentLine)
              = t_->convert(pal_.getColor(tile.get(TilePos { .x = x, .y = static_cast<uint8_t>(currentTileLine) })));
        }
      }
    }
  }
}

auto GbObjects::toTileDataIndex(uint8_t objectTileIndex) const -> uint8_t
{ // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  return lcdc_.testBit(ObjSizeBit) ? 0b1111110U & objectTileIndex : objectTileIndex; // TODO: vollständig
}
