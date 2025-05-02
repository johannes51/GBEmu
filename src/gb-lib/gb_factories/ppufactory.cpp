#include "ppufactory.h"

#include "ppu/gbrenderer.h"
#include "ppu/layer/gbbg.h"
#include "ppu/layer/gbobjects.h"
#include "ppu/layer/gbwindow.h"
#include "ppu/layer/tiledata.h"
#include "ppu/layer/tilemap.h"
#include "ppu/ppu.h"
#include "ppu/ppu_constants.h"
#include "ppuregisterfactory.h"

auto PpuFactory::constructPpu() -> IPpuUP
{
  PpuRegisterFactory rf { mem_ };
  auto lcdc = rf.get(PpuRegisters::LCDC);

  auto bgTm = std::make_unique<TileMap>(
      lcdc, mem_, std::make_unique<TileData>(lcdc, mem_, BgWindowTileDataBit), BgTileMapBit);
  auto bg = std::make_shared<GbBg>(
      lcdc, rf.get(PpuRegisters::SCX), rf.get(PpuRegisters::SCY), rf.get(PpuRegisters::BGP), std::move(bgTm));

  auto winTm = std::make_unique<TileMap>(
      lcdc, mem_, std::make_unique<TileData>(lcdc, mem_, BgWindowTileDataBit), WindowTileMapBit);
  auto win = std::make_shared<GbWindow>(
      lcdc, rf.get(PpuRegisters::WX), rf.get(PpuRegisters::WY), rf.get(PpuRegisters::BGP), std::move(winTm));

  auto obj = std::make_shared<GbObjects>(std::make_unique<Oam>(mem_), lcdc, rf.get(PpuRegisters::OBP0),
      rf.get(PpuRegisters::OBP1), std::make_unique<TileData>(lcdc, mem_));

  return std::make_unique<Ppu>(
      std::make_shared<GbRenderer>(std::move(bg), std::move(win), std::move(obj)), std::move(lcdc));
}
