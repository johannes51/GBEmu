#ifndef GBBG_H
#define GBBG_H

#include "ibackground.h"

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "palette.h"
#include "pos.h"
#include "tileaddress.h"

class TileMap;

class GbBg : public IBackground {
public:
  explicit GbBg(IRegisterAdapterSP lcdc, IRegisterAdapterSP scx, IRegisterAdapterSP scy, IRegisterAdapterSP bgp,
      IMemoryViewSP mem);
  ~GbBg() override;

  void draw(IPixelBuffer& buffer) override;

private:
  std::pair<TileAddress, Pos> decomposePos(uint8_t x, uint8_t y);

  IRegisterAdapterSP lcdc_;
  IRegisterAdapterSP scx_;
  IRegisterAdapterSP scy_;
  IRegisterAdapterSP bgp_;
  std::unique_ptr<TileMap> map_;
  Palette pal_;
};

#endif // GBBG_H
