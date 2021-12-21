#ifndef GBBG_H
#define GBBG_H

#include "ibackground.h"

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "palette.h"

class TileMap;

class GbBg : public IBackground {
public:
  explicit GbBg(IRegisterAdapterSP lcdc, IRegisterAdapterSP scx, IRegisterAdapterSP scy, IRegisterAdapterSP bgp,
      std::unique_ptr<TileMap> map);
  ~GbBg() override;

  void draw(IPixelBuffer& buffer) override;

private:
  IRegisterAdapterSP lcdc_;
  IRegisterAdapterSP scx_;
  IRegisterAdapterSP scy_;
  IRegisterAdapterSP bgp_;
  std::unique_ptr<TileMap> map_;
  Palette pal_;
};

#endif // GBBG_H
