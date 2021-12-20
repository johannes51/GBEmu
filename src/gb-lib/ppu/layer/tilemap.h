#ifndef TILEMAP_H
#define TILEMAP_H

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"

class TileData;

class TileMap {
public:
  explicit TileMap(IRegisterAdapterSP lcdc, IMemoryViewSP mem);
  ~TileMap();

private:
  IRegisterAdapterSP lcdc_;
  IMemoryViewSP mem_;

  std::unique_ptr<TileData> tiles_;
};

#endif // TILEMAP_H
