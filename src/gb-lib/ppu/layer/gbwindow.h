#ifndef GBWINDOW_H
#define GBWINDOW_H

#include "iwindow.h"

#include "colortransformation.h"
#include "gbpalette.h"
#include "mem/registers/iregisteradapter.h"
#include "tiledata.h"
#include "tilemap.h"

class GbWindow : public IWindow {
public:
  explicit GbWindow(const IRegisterAdapter& lcdc, const IRegisterAdapter& wx, const IRegisterAdapter& wy,
      const IRegisterAdapter& bgp, TileDataUP data, TileMapUP map);
  ~GbWindow() override;

  void draw(GbPixelBuffer& buffer, const uint8_t currentLine) override;

private:
  const IRegisterAdapter& lcdc_;
  const IRegisterAdapter& wx_;
  const IRegisterAdapter& wy_;
  const IRegisterAdapter& bgp_;
  TileDataUP data_;
  TileMapUP map_;
  GbPalette pal_;
  GbColorTransformationUP t_;
};

#endif // GBWINDOW_H
