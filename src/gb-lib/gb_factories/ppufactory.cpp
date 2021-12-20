#include "ppufactory.h"

#include "location/location.h"
#include "mem/imemoryview.h"
#include "ppu/gbrenderer.h"
#include "ppu/layer/gbbg.h"
#include "ppu/layer/gbobjects.h"
#include "ppu/layer/gbwindow.h"
#include "ppu/ppu.h"

auto PpuFactory::constructPpu() -> std::shared_ptr<Ppu>
{
  ioBank_->getByte(0x000);
  auto result = std::make_shared<Ppu>(std::make_shared<GbRenderer>(
      std::make_shared<GbBg>(), std::make_shared<GbWindow>(), std::make_shared<GbObjects>()));
  return {};
}
