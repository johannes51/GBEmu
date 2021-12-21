#include "gbbg.h"

#include "../ppu_constants.h"
#include "helper.h"
#include "tilemap.h"

GbBg::GbBg(IRegisterAdapterSP lcdc, IRegisterAdapterSP scx, IRegisterAdapterSP scy, IRegisterAdapterSP bgp,
    std::unique_ptr<TileMap> map)
    : lcdc_(std::move(lcdc))
    , scx_(std::move(scx))
    , scy_(std::move(scy))
    , bgp_(std::move(bgp))
    , map_(std::move(map))
    , pal_(bgp_)
{
}

GbBg::~GbBg() = default;

void GbBg::draw(IPixelBuffer& buffer)
{
  for (uint8_t y = 0; y < LcdWidth; ++y) {
    for (uint8_t x = 0; x < LcdHeight; ++x) {
      auto [tileAddress, tilePos] = decomposePos(x, y, scx_->get(), scy_->get());
      auto tile = map_->getTile(tileAddress);
      buffer[y][x] = static_cast<unsigned char>(pal_.getColor(tile.get(tilePos)));
    }
  }
}
