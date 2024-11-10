#ifndef GBBG_H
#define GBBG_H

#include "ibackground.h"

#include "colortransformation.h"
#include "gbpalette.h"
#include "mem/registers/iregisteradapter.h"
#include "tilemap.h"

class GbBg : public IBackground {
public:
  explicit GbBg(
      IRegisterAdapterSP lcdc, IRegisterAdapterSP scx, IRegisterAdapterSP scy, IRegisterAdapterSP bgp, TileMapUP map);
  ~GbBg() override;

  void draw(GbPixelBuffer& buffer) override;

private:
  IRegisterAdapterSP lcdc_;
  IRegisterAdapterSP scx_;
  IRegisterAdapterSP scy_;
  TileMapUP map_;
  GbPalette pal_;
  GbColorTransformationUP t_;
};

#endif // GBBG_H
