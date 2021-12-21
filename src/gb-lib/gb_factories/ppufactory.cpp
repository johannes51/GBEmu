#include "ppufactory.h"

#include "ppu/gbrenderer.h"
#include "ppu/layer/gbbg.h"
#include "ppu/layer/gbobjects.h"
#include "ppu/layer/gbwindow.h"
#include "ppu/layer/tiledata.h"
#include "ppu/layer/tilemap.h"
#include "ppu/ppu.h"
#include "ppuregisterfactory.h"

auto PpuFactory::constructPpu() -> std::shared_ptr<Ppu>
{
  PpuRegisterFactory rf { mem_ };
  auto lcdc = rf.get(PpuRegisters::LCDC);

  auto bgTm = std::make_unique<TileMap>(lcdc, mem_, std::make_unique<TileData>(lcdc, mem_, 4), 3);
  auto bg = std::make_shared<GbBg>(
      lcdc, rf.get(PpuRegisters::SCX), rf.get(PpuRegisters::SCY), rf.get(PpuRegisters::BGP), std::move(bgTm));

  auto winTm = std::make_unique<TileMap>(lcdc, mem_, std::make_unique<TileData>(lcdc, mem_, 4), 6);
  auto win = std::make_shared<GbWindow>(
      lcdc, rf.get(PpuRegisters::WX), rf.get(PpuRegisters::WY), rf.get(PpuRegisters::BGP), std::move(winTm));

  auto obj = std::make_shared<GbObjects>();

  return std::make_shared<Ppu>(std::make_shared<GbRenderer>(std::move(bg), std::move(win), std::move(obj)));
}
