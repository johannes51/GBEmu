#ifndef GBOBJECTS_H
#define GBOBJECTS_H

#include "iobjects.h"

#include "colortransformation.h"
#include "oam.h"
#include "tiledata.h"

class GbObjects : public IObjects {
public:
  explicit GbObjects(
      OamUP oam, IRegisterAdapterSP lcdc, IRegisterAdapterSP obp1, IRegisterAdapterSP obp2, TileDataUP tileData);
  ~GbObjects() override = default;
  DEFAULT_COPY_AND_MOVE(GbObjects)

  void draw(GbPixelBuffer& buffer, const uint8_t currentLine) override;

private:
  uint8_t toTileDataIndex(uint8_t objectTileIndex) const;

  OamUP oam_;
  IRegisterAdapterSP lcdc_;
  IRegisterAdapterSP obp1_;
  IRegisterAdapterSP obp2_;
  TileDataUP tileData_;
  GbColorTransformationUP t_;
};

#endif // GBOBJECTS_H
