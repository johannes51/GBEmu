#ifndef GBWINDOW_H
#define GBWINDOW_H

#include "iwindow.h"

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "palette.h"
#include "pos.h"
#include "tileaddress.h"

class TileMap;

class GbWindow : public IWindow {
public:
  explicit GbWindow(IRegisterAdapterSP lcdc, IRegisterAdapterSP wx, IRegisterAdapterSP wy, IRegisterAdapterSP bgp,
      std::unique_ptr<TileMap> map);
  ~GbWindow() override;

  void draw(IPixelBuffer& buffer) override;

private:
  IRegisterAdapterSP lcdc_;
  IRegisterAdapterSP wx_;
  IRegisterAdapterSP wy_;
  IRegisterAdapterSP bgp_;
  std::unique_ptr<TileMap> map_;
  Palette pal_;
};

#endif // GBWINDOW_H
