#include "gbbg.h"

#include "tilemap.h"

GbBg::GbBg(
    IRegisterAdapterSP lcdc, IRegisterAdapterSP scx, IRegisterAdapterSP scy, IRegisterAdapterSP bgp, IMemoryViewSP mem)
    : lcdc_(std::move(lcdc))
    , scx_(std::move(scx))
    , scy_(std::move(scy))
    , bgp_(std::move(bgp))
    , map_(std::move(std::make_unique<TileMap>(lcdc_, std::move(mem))))
{
}

GbBg::~GbBg() = default;

void GbBg::draw(IPixelBuffer& buffer) { }
