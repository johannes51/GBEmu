#include "tiledata.h"

TileData::TileData(IRegisterAdapterSP lcdc, IMemoryViewSP mem)
    : lcdc_(std::move(lcdc))
    , mem_(std::move(mem))
{
}
