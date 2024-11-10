#ifndef GBWINDOW_H
#define GBWINDOW_H

#include "iwindow.h"

#include "colortransformation.h"
#include "gbpalette.h"
#include "mem/registers/iregisteradapter.h"
#include "tilemap.h"

class GbWindow : public IWindow {
public:
  explicit GbWindow(
      IRegisterAdapterSP lcdc, IRegisterAdapterSP wx, IRegisterAdapterSP wy, IRegisterAdapterSP bgp, TileMapUP map);
  ~GbWindow() override;

  void draw(GbPixelBuffer& buffer) override;

private:
  IRegisterAdapterSP lcdc_;
  IRegisterAdapterSP wx_;
  IRegisterAdapterSP wy_;
  IRegisterAdapterSP bgp_;
  TileMapUP map_;
  GbPalette pal_;
  GbColorTransformationUP t_;
};

#endif // GBWINDOW_H
