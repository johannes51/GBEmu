#ifndef TILEDATA_H
#define TILEDATA_H

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"

class TileData {
public:
  explicit TileData(IRegisterAdapterSP lcdc, IMemoryViewSP mem);

private:
  IRegisterAdapterSP lcdc_;
  IMemoryViewSP mem_;
};

#endif // TILEDATA_H
