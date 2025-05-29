#include "ppufactory.h"

#include "ppu/gbrenderer.h"
#include "ppu/layer/gbbg.h"
#include "ppu/layer/gbobjects.h"
#include "ppu/layer/gbwindow.h"
#include "ppu/layer/tiledata.h"
#include "ppu/layer/tilemap.h"
#include "ppu/ppu.h"
#include "ppu/ppu_constants.h"

auto PpuFactory::constructPpu() -> IPpuUP
{
  auto result = std::make_unique<Ppu>(ioBank_, if_, std::move(vram_), std::move(oam_));

  auto bgTm = std::make_unique<TileMap>(result->getLcdc(), mem_, BgTileMapBit);
  auto bg = std::make_unique<GbBg>(result->getLcdc(), result->getScx(), result->getScy(), result->getBgp(),
      std::make_unique<TileData>(result->getLcdc(), mem_, BgWindowTileDataBit), std::move(bgTm));

  auto winTm = std::make_unique<TileMap>(result->getLcdc(), mem_, WindowTileMapBit);
  auto win = std::make_unique<GbWindow>(result->getLcdc(), result->getWx(), result->getWy(), result->getBgp(),
      std::make_unique<TileData>(result->getLcdc(), mem_, BgWindowTileDataBit), std::move(winTm));

  auto obj = std::make_unique<GbObjects>(std::make_unique<Oam>(mem_), result->getLcdc(), result->getObp0(),
      result->getObp1(), result->getBgp(), std::make_unique<TileData>(result->getLcdc(), mem_));

  result->setRenderer(std::make_unique<GbRenderer>(std::move(bg), std::move(win), std::move(obj)));

  return result;
}
