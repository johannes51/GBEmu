#ifndef GBBG_H
#define GBBG_H

#include "ibackground.h"

#include "colortransformation.h"
#include "gbpalette.h"
#include "mem/registers/iregisteradapter.h"
#include "tiledata.h"
#include "tilemap.h"

class GbBg : public IBackground {
public:
  explicit GbBg(const IRegisterAdapter& lcdc, const IRegisterAdapter& scx, const IRegisterAdapter& scy,
      const IRegisterAdapter& bgp, TileDataUP data, TileMapUP map);
  ~GbBg() override = default;

  void draw(GbPixelBuffer& buffer, const uint8_t currentLine) override;

private:
  const IRegisterAdapter& lcdc_;
  const IRegisterAdapter& scx_;
  const IRegisterAdapter& scy_;
  TileDataUP data_;
  TileMapUP map_;
  GbPalette pal_;
  GbColorTransformationUP t_;
};

#endif // GBBG_H
