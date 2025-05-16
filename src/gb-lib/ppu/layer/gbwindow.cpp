#include "gbwindow.h"

#include "../ppu_constants.h"
#include "helper.h"
#include "tilemap.h"

GbWindow::GbWindow(const IRegisterAdapter& lcdc, const IRegisterAdapter& wx, const IRegisterAdapter& wy,
    const IRegisterAdapter& bgp, TileDataUP data, TileMapUP map)
    : lcdc_(lcdc)
    , wx_(wx)
    , wy_(wy)
    , bgp_(bgp)
    , data_(std::move(data))
    , map_(std::move(map))
    , pal_(bgp_)
    , t_(GbColorTransformation::makeGbStdRgb())
{
}

GbWindow::~GbWindow() = default;

void GbWindow::draw(GbPixelBuffer& buffer, const uint8_t currentLine)
{
  if (!lcdc_.testBit(WindowEnableBit) || !lcdc_.testBit(BgWindowEnablePrioBit)) {
    return;
  }
  for (uint8_t x = wx_.getByte(); x < LcdWidth; ++x) {
    auto [tileAddress, tilePos] = decomposePos(x, currentLine, -wx_.getByte(), -wy_.getByte());
    const auto tileIndex = map_->getIndex(tileAddress);
    auto tile = data_->getTile(tileIndex);
    buffer.at(x, currentLine) = t_->convert(pal_.getColor(tile.get(tilePos)));
  }
}
