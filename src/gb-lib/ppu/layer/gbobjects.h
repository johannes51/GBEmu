#ifndef GBOBJECTS_H
#define GBOBJECTS_H

#include "iobjects.h"

#include "colortransformation.h"
#include "oam.h"
#include "tiledata.h"

class GbObjects : public IObjects {
public:
  explicit GbObjects(OamUP oam, const IRegisterAdapter& lcdc, const IRegisterAdapter& obp1,
      const IRegisterAdapter& obp2, const IRegisterAdapter& bgp, TileDataUP tileData);
  ~GbObjects() override = default;
  DEFAULT_COPY_AND_MOVE(GbObjects)

  void draw(GbPixelBuffer& buffer, const uint8_t currentLine) override;

private:
  uint8_t toTileDataIndex(uint8_t objectTileIndex) const;

  static constexpr int ObjVertOffset = 16U;

  OamUP oam_;
  const IRegisterAdapter& lcdc_;
  const IRegisterAdapter& obp1_;
  const IRegisterAdapter& obp2_;
  TileDataUP tileData_;
  GbPalette pal_;
  GbColorTransformationUP t_;
};

#endif // GBOBJECTS_H
