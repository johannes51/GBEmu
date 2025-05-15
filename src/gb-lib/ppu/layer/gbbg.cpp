#include "gbbg.h"

#include "../ppu_constants.h"
#include "helper.h"
#include "tilemap.h"

GbBg::GbBg(IRegisterAdapterSP lcdc, IRegisterAdapterSP scx, IRegisterAdapterSP scy, IRegisterAdapterSP bgp,
    TileDataUP data, TileMapUP map)
    : lcdc_(std::move(lcdc))
    , scx_(std::move(scx))
    , scy_(std::move(scy))
    , data_(std::move(data))
    , map_(std::move(map))
    , pal_(std::move(bgp))
    , t_(GbColorTransformation::makeGbStdRgb())
{
}

void GbBg::draw(GbPixelBuffer& buffer, const uint8_t currentLine)
{
  if (!lcdc_->testBit(BgWindowEnablePrioBit)) {
    for (uint8_t x = 0; x < LcdWidth; ++x) {
      buffer.at(x, currentLine) = t_->convert(GbColors::White);
    }
  } else {
    for (uint8_t x = 0; x < LcdWidth; ++x) {
      auto [tileAddress, tilePos] = decomposePos(x, currentLine, scx_->get(), scy_->get());
      const auto tileIndex = map_->getIndex(tileAddress);
      auto tile = data_->getTile(tileIndex);
      buffer.at(x, currentLine) = t_->convert(pal_.getColor(tile.get(tilePos)));
    }
  }
}
