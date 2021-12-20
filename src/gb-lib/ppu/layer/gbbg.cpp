#include "gbbg.h"

#include "tilemap.h"

GbBg::GbBg(
    IRegisterAdapterSP lcdc, IRegisterAdapterSP scx, IRegisterAdapterSP scy, IRegisterAdapterSP bgp, IMemoryViewSP mem)
    : lcdc_(std::move(lcdc))
    , scx_(std::move(scx))
    , scy_(std::move(scy))
    , bgp_(std::move(bgp))
    , map_(std::make_unique<TileMap>(lcdc_, std::move(mem)))
{
}

GbBg::~GbBg() = default;

void GbBg::draw(IPixelBuffer& buffer)
{
  for (uint8_t y = 0; y < 144; ++y) {
    for (uint8_t x = 0; x < 160; ++x) {
      auto [tileAddress, tilePos] = decomposePos(x, y);
      auto tile = map_->getTile(tileAddress);
      tile.get(tilePos.first, tilePos.second);
    }
  }
}

auto GbBg::decomposePos(uint8_t x, uint8_t y) -> std::pair<TileAddress, std::pair<uint8_t, uint8_t>> { return {}; }
