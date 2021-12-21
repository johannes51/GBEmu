#include "ppufactory.h"

#include "ppu/gbrenderer.h"
#include "ppu/layer/gbbg.h"
#include "ppu/layer/gbobjects.h"
#include "ppu/layer/gbwindow.h"
#include "ppu/ppu.h"
#include "ppuregisterfactory.h"

auto PpuFactory::constructPpu() -> std::shared_ptr<Ppu>
{
  PpuRegisterFactory rf { mem_ };
  auto result = std::make_shared<Ppu>(
      std::make_shared<GbRenderer>(std::make_shared<GbBg>(rf.get(PpuRegisters::LCDC), rf.get(PpuRegisters::SCX),
                                       rf.get(PpuRegisters::SCY), rf.get(PpuRegisters::BGP), mem_),
          std::make_shared<GbWindow>(rf.get(PpuRegisters::LCDC), rf.get(PpuRegisters::WX), rf.get(PpuRegisters::WY),
              rf.get(PpuRegisters::BGP), mem_),
          std::make_shared<GbObjects>()));
  return result;
}
