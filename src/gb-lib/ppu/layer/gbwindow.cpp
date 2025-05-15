#include "gbwindow.h"

#include "../ppu_constants.h"
#include "helper.h"
#include "tilemap.h"

GbWindow::GbWindow(IRegisterAdapterSP lcdc, IRegisterAdapterSP wx, IRegisterAdapterSP wy, IRegisterAdapterSP bgp,
    TileDataUP data, TileMapUP map)
    : lcdc_(std::move(lcdc))
    , wx_(std::move(wx))
    , wy_(std::move(wy))
    , bgp_(std::move(bgp))
    , data_(std::move(data))
    , map_(std::move(map))
    , pal_(bgp_)
    , t_(GbColorTransformation::makeGbStdRgb())
{
}

GbWindow::~GbWindow() = default;

void GbWindow::draw(GbPixelBuffer& buffer, const uint8_t currentLine)
{
  if (!lcdc_->testBit(WindowEnableBit) || !lcdc_->testBit(BgWindowEnablePrioBit)) {
    return;
  }
  for (uint8_t x = wx_->get(); x < LcdWidth; ++x) {
    auto [tileAddress, tilePos] = decomposePos(x, currentLine, -wx_->get(), -wy_->get());
    const auto tileIndex = map_->getIndex(tileAddress);
    auto tile = data_->getTile(tileIndex);
    buffer.at(x, currentLine) = t_->convert(pal_.getColor(tile.get(tilePos)));
  }
}
