#include "gbbg.h"

#include "tilemap.h"

GbBg::GbBg(
    IRegisterAdapterSP lcdc, IRegisterAdapterSP scx, IRegisterAdapterSP scy, IRegisterAdapterSP bgp, IMemoryViewSP mem)
    : lcdc_(std::move(lcdc))
    , scx_(std::move(scx))
    , scy_(std::move(scy))
    , bgp_(std::move(bgp))
    , map_(std::make_unique<TileMap>(lcdc_, std::move(mem)))
    , pal_(bgp_)
{
}

GbBg::~GbBg() = default;

void GbBg::draw(IPixelBuffer& buffer)
{
  for (uint8_t y = 0; y < 144; ++y) {
    for (uint8_t x = 0; x < 160; ++x) {
      auto [tileAddress, tilePos] = decomposePos(x, y);
      auto tile = map_->getTile(tileAddress);
      buffer[y][x] = static_cast<unsigned char>(pal_.getColor(tile.get(tilePos)));
    }
  }
}

auto GbBg::decomposePos(uint8_t x, uint8_t y) -> std::pair<TileAddress, Pos>
{
  auto ta = TileAddress { static_cast<uint8_t>(x / 8U), static_cast<uint8_t>(y / 8U) };
  auto po = Pos { static_cast<uint8_t>(x % 8U), static_cast<uint8_t>(y % 8U) };
  return { ta, po };
}
