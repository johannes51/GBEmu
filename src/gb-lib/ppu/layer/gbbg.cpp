#include "gbbg.h"

#include "../ppu_constants.h"
#include "helper.h"
#include "tilemap.h"

GbBg::GbBg(const IRegisterAdapter& lcdc, const IRegisterAdapter& scx, const IRegisterAdapter& scy,
    const IRegisterAdapter& bgp, TileDataUP data, TileMapUP map)
    : lcdc_(lcdc)
    , scx_(scx)
    , scy_(scy)
    , data_(std::move(data))
    , map_(std::move(map))
    , pal_(bgp)
    , t_(GbColorTransformation::makeGbStdRgb())
{
}

void GbBg::draw(GbPixelBuffer& buffer, const uint8_t currentLine)
{
  if (!lcdc_.testBit(BgWindowEnablePrioBit)) {
    for (uint8_t x = 0; x < LcdWidth; ++x) {
      buffer.at(x, currentLine) = t_->convert(GbColors::White);
    }
  } else {
    for (uint8_t x = 0; x < LcdWidth; ++x) {
      auto [tileAddress, tilePos] = decomposePos(x, currentLine, scx_.getByte(), scy_.getByte());
      const auto tileIndex = map_->getIndex(tileAddress);
      auto tile = data_->getTile(tileIndex);
      buffer.at(x, currentLine) = t_->convert(pal_.getColor(tile.get(tilePos)));
    }
  }
}
