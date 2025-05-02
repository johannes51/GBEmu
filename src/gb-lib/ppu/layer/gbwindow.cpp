#include "gbwindow.h"

#include "../ppu_constants.h"
#include "helper.h"
#include "tilemap.h"

GbWindow::GbWindow(
    IRegisterAdapterSP lcdc, IRegisterAdapterSP wx, IRegisterAdapterSP wy, IRegisterAdapterSP bgp, TileMapUP map)
    : lcdc_(std::move(lcdc))
    , wx_(std::move(wx))
    , wy_(std::move(wy))
    , bgp_(std::move(bgp))
    , map_(std::move(map))
    , pal_(bgp_)
    , t_(GbColorTransformation::makeGbStdRgb())
{
}

GbWindow::~GbWindow() = default;

void GbWindow::draw(GbPixelBuffer& buffer, const uint8_t currentLine)
{
  for (uint8_t x = wx_->get(); x < LcdWidth; ++x) {
    auto [tileAddress, tilePos] = decomposePos(x, currentLine, -wx_->get(), -wy_->get());
    auto tile = map_->getTile(tileAddress);
    buffer.at(x, currentLine) = t_->convert(pal_.getColor(tile.get(tilePos)));
  }
}
