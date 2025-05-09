#include "gbbg.h"

#include "../ppu_constants.h"
#include "helper.h"
#include "tilemap.h"

GbBg::GbBg(
    IRegisterAdapterSP lcdc, IRegisterAdapterSP scx, IRegisterAdapterSP scy, IRegisterAdapterSP bgp, TileMapUP map)
    : lcdc_(std::move(lcdc))
    , scx_(std::move(scx))
    , scy_(std::move(scy))
    , map_(std::move(map))
    , pal_(std::move(bgp))
    , t_(GbColorTransformation::makeGbStdRgb())
{
}

void GbBg::draw(GbPixelBuffer& buffer)
{
  for (uint8_t x = 0; x < LcdWidth; ++x) {
    for (uint8_t y = 0; y < LcdHeight; ++y) {
      auto [tileAddress, tilePos] = decomposePos(x, y, scx_->get(), scy_->get());
      auto tile = map_->getTile(tileAddress);
      buffer.at(x, y) = t_->convert(pal_.getColor(tile.get(tilePos)));
    }
  }
}
